#pragma once

#include "WAVM/IR/Value.h"
#include "WAVM/Platform/File.h"
#include "WAVM/Runtime/Runtime.h"
#include "WAVM/VFS/SandboxFS.h"
#include "WAVM/WASI/WASI.h"
#include "wasm_sandbox/backend/region.h"
#include "wasm_sandbox/sandbox.h"
#include "wasm_sandbox/wasm/embedder_resolver.h"

#include <memory>
#include <vector>

using namespace WAVM;
using namespace WAVM::WASI;
using namespace WAVM::Runtime;

namespace sandbox
{
  /**
   * WASMLibrary implementation.
   */
  class WASMLibrary : public Library
  {
    struct State
    {
      GCPointer<Compartment> compartment;
      GCPointer<Context> context;
      GCPointer<Instance> intrinsics;
      GCPointer<Instance> instance;
      Memory* memory;

    public:
      State(GCPointer<Compartment> c)
      : compartment(c), context(createContext(c)), memory(nullptr)
      {}

      ~State()
      {
        intrinsics = nullptr;
        instance = nullptr;
        context = nullptr;
        WAVM_ERROR_UNLESS(tryCollectCompartment(std::move(compartment)));
      }
    };

  private:
    const char* library_name = nullptr;
    WAVM::Runtime::ModuleRef module = nullptr;
    std::unique_ptr<State> state;
    std::shared_ptr<WASI::Process> process;
    std::shared_ptr<VFS::FileSystem> sandboxFS;
    std::unique_ptr<EmbedderResolver> resolver;
    std::shared_ptr<allocator::Region> region;

    /**
     * Returns true if the ptr address is within the WASM memory range.
     */
    bool is_valid_address(void* ptr);

    /**
     * Returns true if the offset is within the WASM memory.
     */
    bool is_valid_offset(int32_t offset);

    /**
     * Ensures the LLVM thunks are instantiated.
     */
    void generate_thunks();

  public:
    WASMLibrary(const char* libname, bool instantiate = true);
    ~WASMLibrary();

    /// Run the specified function.
    void call(
      char const* name,
      std::vector<IR::Value>& invokeArgs,
      std::vector<IR::Value>& invokResults);

    void instantiate(WAVM::Intrinsics::Module* modules...);
    /**
     * Stack of currently opened libraries.
     */
    static WASMLibrary*& get_library();

    /**
     * Calcultes the memory offset for a given pointer.
     */
    int32_t sb_memory_offset(void* ptr);

    /**
     * Converts a sandbox memory offset into a valid pointer.
     */
    void* ptr_from_memory_offset(int32_t offset);
    virtual void send(int index, void* ptr);
    virtual void* alloc_in_sandbox(size_t bytes, size_t count = 1);
    virtual void free_in_sandbox(void* ptr);
  };
} // namespace sandbox
