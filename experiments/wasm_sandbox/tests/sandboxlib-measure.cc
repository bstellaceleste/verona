#include "sandbox-measure.h"
#include "wasm_sandbox/sandbox.h"
#include "wasm_sandbox/sandbox/cxxsandbox.h"

#include <cstdio>
#include <cstdlib>
__attribute__((__import_module__("env"), __import_name__("external_call"))) void
external_call(int a, int b);

__attribute__((export_name("alloc_in_sandbox"))) void*
alloc_in_sandbox(size_t count)
{
  return malloc(count);
}

__attribute__((export_name("free_in_sandbox"))) void free_in_sandbox(void* ptr)
{
  free(ptr);
}

void call_back(void)
{
  for (int i = 0; i < REPS; i++)
  {
    external_call(i, i * 2);
  }
}

void local_func(int a, int b)
{
  a = a + b;
}

void call_local(void)
{
  for (int i = 0; i < REPS; i++)
  {
    local_func(i, 2 * i);
  }
}

__attribute__((export_name("proxy"))) void proxy(int idx, void* args)
{
  sandbox::sandbox_call(idx, args);
}

__attribute__((export_name("sandbox_init"))) void sandbox_init()
{
  sandbox::ExportedLibrary::export_function(::call_back);
  sandbox::ExportedLibrary::export_function(::call_local);
}
