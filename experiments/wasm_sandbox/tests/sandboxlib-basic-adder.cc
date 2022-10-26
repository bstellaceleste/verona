#include "wasm_sandbox/sandbox.h"
#include "wasm_sandbox/sandbox/cxxsandbox.h"

#include <cstdio>
#include <cstdlib>

static int Global = 0;

__attribute__((export_name("sum"))) int sum(int a, int b)
{
  printf("In sum %d %d\n", a, b);
  return a + b;
}

__attribute__((export_name("simple_print"))) void simple_print()
{
  printf("Oh damn! %d\n", Global);
  Global++;
}

__attribute__((export_name("alloc_dealloc"))) void alloc_dealloc()
{
  int* a = (int*)malloc(sizeof(int));
  *a = 666;
  printf("The value of a %d\n", *a);
  free(a);
}

__attribute__((export_name("alloc_in_sandbox"))) void*
alloc_in_sandbox(size_t count)
{
  return malloc(count);
}

__attribute__((export_name("free_in_sandbox"))) void free_in_sandbox(void* ptr)
{
  free(ptr);
}

__attribute__((export_name("proxy"))) void proxy(int idx, void* args)
{
  sandbox::sandbox_call(idx, args);
}

__attribute__((export_name("sandbox_init"))) void sandbox_init()
{
  sandbox::ExportedLibrary::export_function(::sum);
  sandbox::ExportedLibrary::export_function(::simple_print);
}
