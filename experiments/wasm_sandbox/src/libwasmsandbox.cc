#include "WAVM/IR/Types.h"
#include "WAVM/IR/Value.h"
#include "WAVM/LLVMJIT/LLVMJIT.h"
#include "WAVM/Runtime/Intrinsics.h"
#include "WAVM/Runtime/Linker.h"
#include "WAVM/Runtime/Runtime.h"
#include "WAVM/RuntimeABI/RuntimeABI.h"
#include "WAVM/WASI/WASI.h"
#include "WAVM/WASM/WASM.h"
#include "wasm_sandbox/wasm/embedder_resolver.h"
#include "wasm_sandbox/wasm/snmalloc_embeddings.h"
#include "wasm_sandbox/wasm/utils.h"
#include "wasm_sandbox/wasm/wasmsandbox.h"

#include <WAVM/Runtime/Intrinsics.h>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <snmalloc/snmalloc.h>
#include <vector>

using namespace WAVM::IR;
using namespace sandbox::backend::utils;

namespace sandbox
{
  // ——————————————————————— WASMLibrary Implementation ———————————————————————

  WASMLibrary::WASMLibrary(const char* library_name, bool instantiate)
  : library_name(library_name)
  {
    std::vector<WAVM::U8> wasmBytes;
    if (!readFile(library_name, wasmBytes))
    {
      std::cerr << "Unable to readfile '" << library_name << "'" << std::endl;
      abort();
    }

    WAVM::WASM::LoadError loadError;
    if (!loadBinaryModule(
          wasmBytes.data(),
          wasmBytes.size(),
          module,
          FeatureLevel::proposed,
          &loadError))
    {
      std::cerr << "Could not load '" << library_name
                << "':" << loadError.message << std::endl;
      abort();
    }
    // Initialize the state.
    state = std::make_unique<State>(createCompartment());
    std::vector<std::string> wasiArgs;
    sandboxFS = VFS::makeSandboxFS(
      &Platform::getHostFS(), Platform::getCurrentWorkingDirectory());
    process = createProcess(
      state->compartment,
      std::move(wasiArgs),
      {},
      sandboxFS.get(),
      Platform::getStdFD(Platform::StdDevice::in),
      Platform::getStdFD(Platform::StdDevice::out),
      Platform::getStdFD(Platform::StdDevice::err));

    if (instantiate)
    {
      this->instantiate({});
    }
  }

  void WASMLibrary::instantiate(WAVM::Intrinsics::Module* modules...)
  {
    // Instantiate intrinsic module reference and functions.
    if (modules)
    {
      state->intrinsics = WAVM::Intrinsics::instantiateModule(
        state->compartment, {WAVM_INTRINSIC_MODULE_REF(env), modules}, "env");
    }
    else
    {
      state->intrinsics = WAVM::Intrinsics::instantiateModule(
        state->compartment, {WAVM_INTRINSIC_MODULE_REF(env)}, "env");
    }

    // Create a resolver for this module and the process resolver.
    Resolver& presolver = getProcessResolver(*process);
    resolver =
      std::make_unique<EmbedderResolver>("env", state->intrinsics, &presolver);

    // Link the WASM module with the WASI exports.
    LinkResult linkResult = linkModule(getModuleIR(module), *resolver);
    if (!linkResult.success)
    {
      fprintf(stderr, "Failed to link '%s':\n", library_name);
      for (const auto& missingImport : linkResult.missingImports)
      {
        fprintf(
          stderr,
          "Failed to resolve import: type=%s module=%s export=%s\n",
          asString(missingImport.type).c_str(),
          missingImport.moduleName.c_str(),
          missingImport.exportName.c_str());
      }
      abort();
    }
    state->instance = instantiateModule(
      state->compartment,
      module,
      std::move(linkResult.resolvedImports),
      std::string(library_name));
    state->memory =
      asMemoryNullable(getInstanceExport(state->instance, "memory"));
    if (state->memory)
    {
      setProcessMemory(*process, state->memory);
      void* base = getMemoryBaseAddress(this->state->memory);
      size_t size =
        getMemoryNumPages(this->state->memory) * IR::numBytesPerPage;
      region = std::make_shared<allocator::Region>(base, size);
    }
    else
    {
      fprintf(stderr, "Failed to find memory export in '%s'.\n", library_name);
      abort();
    }

    // Initialize the sandbox.
    std::vector<Value> args;
    std::vector<Value> res;
    this->generate_thunks();
    this->call("sandbox_init", args, res);

    // TODO debugging.
    std::shared_ptr<LLVMJIT::Module> jit = accessJitModule(state->instance);
    if (jit == nullptr)
    {
      fprintf(stderr, "Failing to access the jitModule\n");
      abort();
    }
    // Incomplete type as well.
    // jit.get()->memoryManager;
    SectionInfo info;
    if (getMemorySection(jit.get(), AccessRights::SectionType::Execute, &info))
    {
      fprintf(stderr, "Something went wrong accessing the section.\n");
    }
    else
    {
      fprintf(stdout, "We have a section: %lx\n", info.base);
    }
  }

  void WASMLibrary::generate_thunks()
  {
    const std::vector<Object*>& exports = getInstanceExports(state->instance);
    for (Object* e : exports)
    {
      if (!isA(e, IR::ExternKind::function))
        continue;
      Function* func = asFunction(e);
      const FunctionType functype = getFunctionType(func);
      LLVMJIT::getInvokeThunk(functype);
    }
    const std::vector<Object*>& intrinsics =
      getInstanceExports(state->intrinsics);
    for (auto e : intrinsics)
    {
      if (!isA(e, IR::ExternKind::function))
        continue;
      Function* func = asFunction(e);
      const FunctionType functype = getFunctionType(func);
      LLVMJIT::getInvokeThunk(functype);
    }
  }

  WASMLibrary::~WASMLibrary()
  {
    process.reset();
  }

  void WASMLibrary::call(
    char const* name,
    std::vector<Value>& invokeArgs,
    std::vector<Value>& invokeResults)
  {
    Function* func =
      asFunctionNullable(getInstanceExport(state->instance, name));
    if (!func)
    {
      // TODO figure out error handling.
      std::cerr << "Module does not export '" << std::string(name) << "'"
                << std::endl;
      abort();
    }
    const FunctionType functype = getFunctionType(func);
    if (functype.params().size() != invokeArgs.size())
    {
      std::cerr << std::string(name) << " expects " << functype.params().size();
      std::cerr << " arguments, received " << invokeArgs.size() << std::endl;
      abort();
    }
    // Split the tagged argument values into their types and untagged values.
    std::vector<ValueType> invokeArgTypes;
    std::vector<UntaggedValue> untaggedInvokeArgs;
    for (const Value& arg : invokeArgs)
    {
      invokeArgTypes.push_back(arg.type);
      untaggedInvokeArgs.push_back(arg);
    }

    // Infer the expected type of the function from the number and type of the
    // invoke's arguments and the function's actual result types.
    const FunctionType invokeSig(
      getFunctionType(func).results(), TypeTuple(invokeArgTypes));
    // Allocate an array to receive the invoke results.
    std::vector<UntaggedValue> untaggedInvokeResults;
    untaggedInvokeResults.resize(invokeSig.results().size());

    // Set the current library.
    WASMLibrary*& ref = get_library();
    WASMLibrary* prev = ref;
    ref = this;

    // Invoke the function.
    invokeFunction(
      state->context,
      func,
      invokeSig,
      untaggedInvokeArgs.data(),
      untaggedInvokeResults.data());

    // Convert the untagged result values to tagged values.
    invokeResults.resize(invokeSig.results().size());
    for (Uptr resultIndex = 0; resultIndex < untaggedInvokeResults.size();
         resultIndex++)
    {
      const ValueType resultType = invokeSig.results()[resultIndex];
      const UntaggedValue& untaggedResult = untaggedInvokeResults[resultIndex];
      invokeResults[resultIndex] = Value(resultType, untaggedResult);
    }
    // Reset th current library
    ref = prev;
  }

  bool WASMLibrary::is_valid_address(void* ptr)
  {
    uint64_t addr = (uint64_t)ptr;
    uint64_t base = (uint64_t)getMemoryBaseAddress(this->state->memory);
    uint64_t size =
      (uint64_t)getMemoryNumPages(this->state->memory) * IR::numBytesPerPage;
    return (addr >= base && addr < (base + size));
  }

  bool WASMLibrary::is_valid_offset(int32_t offset)
  {
    uint64_t size =
      (uint64_t)getMemoryNumPages(this->state->memory) * IR::numBytesPerPage;
    return (offset < size);
  }

  int32_t WASMLibrary::sb_memory_offset(void* ptr)
  {
    assert(is_valid_address(ptr));
    uint64_t base = (uint64_t)getMemoryBaseAddress(this->state->memory);
    int32_t offset = (int32_t)(((uint64_t)ptr) - base);
    return offset;
  }

  void* WASMLibrary::ptr_from_memory_offset(int32_t offset)
  {
    assert(is_valid_offset(offset));
    uint8_t* base = (uint8_t*)getMemoryBaseAddress(this->state->memory);
    return (void*)(base + offset);
  }

  void* WASMLibrary::alloc_in_sandbox(size_t bytes, size_t count)
  {
#ifdef WASI_ALLOCATOR
    assert(count < INT32_MAX);
    uint32_t size = (int32_t)count;
    std::vector<Value> args;
    std::vector<Value> result;
    args.push_back(I32(size));
    this->call("alloc_in_sandbox", args, result);
    return ptr_from_memory_offset(result[0].i32);
#else
    bool overflow = false;
    size_t sz = snmalloc::bits::umul(bytes, count, overflow);
    if (overflow)
    {
      return nullptr;
    }
    auto& a = region->alloc;
    return a.alloc(sz);
#endif
  }

  void WASMLibrary::free_in_sandbox(void* ptr)
  {
#ifdef WASI_ALLOCATOR
    assert(is_valid_address(ptr));
    int32_t offset = sb_memory_offset(ptr);
    std::vector<Value> args;
    std::vector<Value> ret;
    args.push_back(I32(offset));
    this->call("free_in_sandbox", args, ret);
#else
    assert(is_valid_address(ptr));
    auto& a = region->alloc;
    a.dealloc(ptr);
#endif
  }

  void WASMLibrary::send(int index, void* ptr)
  {
    assert(is_valid_address(ptr));
    int32_t offset = sb_memory_offset(ptr);
    std::vector<Value> args;
    std::vector<Value> res;
    args.push_back(I32(index));
    args.push_back(I32(offset));
    this->call("proxy", args, res);
  }

  // ——————————————————————————— Allocator Accesses ———————————————————————————

  WASMLibrary*& WASMLibrary::get_library()
  {
    static thread_local WASMLibrary* current;
    return current;
  }

} // namespace sandbox.
