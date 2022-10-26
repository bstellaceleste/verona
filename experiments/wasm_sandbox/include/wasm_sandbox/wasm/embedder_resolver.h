#pragma once
#include "WAVM/Runtime/Intrinsics.h"
#include "WAVM/Runtime/Linker.h"
#include "WAVM/Runtime/Runtime.h"
#include "WAVM/WASM/WASM.h"

using namespace WAVM;
using namespace WAVM::WASI;
using namespace WAVM::Runtime;

namespace sandbox
{
  /**
   * Custom resolver for the sandbox embeddings.
   * For the moment we have allocation-related embedders in the "env" module.
   * We can combine/chain resolvers to handle more modules at once.
   */
  struct EmbedderResolver : Resolver
  {
    HashMap<std::string, GCPointer<Instance>> embeddings;
    std::optional<Resolver*> prev;

    EmbedderResolver(
      std::string name,
      GCPointer<Instance> embedder,
      std::optional<Resolver*> prev)
    : prev(prev)
    {
      embeddings.set(name, embedder);
    }

    bool resolve(
      const std::string& moduleName,
      const std::string& exportName,
      IR::ExternType type,
      Runtime::Object*& outObject) override
    {
      const auto& namedInstance = embeddings.get(moduleName);
      if (namedInstance)
      {
        outObject = getInstanceExport(*namedInstance, exportName);
        if (outObject)
        {
          if (isA(outObject, type))
          {
            return true;
          }
          else
          {
            Log::printf(
              Log::debug,
              "Resolved import %s.%s to a %s, but was expecting %s\n",
              moduleName.c_str(),
              exportName.c_str(),
              asString(getExternType(outObject)).c_str(),
              asString(type).c_str());
            return false;
          }
        }
      }
      if (prev.has_value())
        return prev.value()->resolve(moduleName, exportName, type, outObject);
      return false;
    }

    void combine(EmbedderResolver other)
    {
      for (auto entry : other.embeddings)
      {
        if (embeddings.contains(entry.key))
          abort();
        embeddings.set(entry.key, entry.value);
      }
    }
  };
} // namespace sandbox
