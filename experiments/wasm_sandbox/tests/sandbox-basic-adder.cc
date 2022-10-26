#include "wasm_sandbox/sandbox/cxxsandbox.h"
#include "wasm_sandbox/wasm/wasmsandbox.h"

#include <cassert>
#include <iostream>

using namespace sandbox;

int sum(int, int);
void simple_print(void);

struct AddSandbox
{
  /**
   * The library that defines the functions exposed by the sandbox.
   */
  WASMLibrary lib = {SANDBOX_LIBRARY};
#define EXPORTED_FUNCTION(public_name, private_name) \
  decltype(make_sandboxed_function<decltype(private_name)>(lib)) public_name = \
    make_sandboxed_function<decltype(private_name)>(lib);
  EXPORTED_FUNCTION(sum, ::sum)
  EXPORTED_FUNCTION(simple_print, ::simple_print)
};

int main(void)
{
  AddSandbox sb;
  sb.simple_print();
  sb.simple_print();
  assert(12 == sb.sum(10, 2));
  return 0;
}
