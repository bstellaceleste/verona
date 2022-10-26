#include "sandbox-measure.h"

#include "WAVM/IR/Module.h"
#include "WAVM/Runtime/Intrinsics.h"
#include "WAVM/Runtime/Runtime.h"
#include "sandbox-measure.h"
#include "wasm_sandbox/sandbox/cxxsandbox.h"
#include "wasm_sandbox/wasm/wasmsandbox.h"

#include <cassert>
#include <chrono>
#include <iostream>
#include <vector>
using namespace std::chrono;
using namespace sandbox;

void call_back(void);
void call_local(void);

// ——————————————————————— Defining embedder callback ——————————————————————— //
WAVM_DEFINE_INTRINSIC_MODULE(env)
WAVM_DEFINE_INTRINSIC_FUNCTION(
  env, "external_call", void, external_call, I32 a, I32 b)
{
  // TODO not doing anything
}

struct CallBack
{
  /**
   * The library that defines the functions exposed by the sandbox.
   */
  WASMLibrary lib = {SANDBOX_LIBRARY, false};
#define EXPORTED_FUNCTION(public_name, private_name) \
  decltype(make_sandboxed_function<decltype(private_name)>(lib)) public_name = \
    make_sandboxed_function<decltype(private_name)>(lib);
  EXPORTED_FUNCTION(call_back, ::call_back)
  EXPORTED_FUNCTION(call_local, ::call_local)
};

void measure(sandbox::Function<void> fn, std::string message, double nb)
{
  std::cout << message << " in us" << std::endl;
  auto start = high_resolution_clock::now();
  fn();
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  auto nanosec = duration_cast<nanoseconds>(stop - start);
  auto per_rep = nanosec.count() / nb;
  std::cout << duration.count() << "(" << per_rep << " ns/call)" << std::endl;
}

[[clang::optnone]] void measure_instantiate()
{
  auto start = high_resolution_clock::now();
  for (int i = 0; i < REPS_INSTANTIATE; i++)
  {
    CallBack sb;
  }
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<seconds>(stop - start);
  auto per_rep = duration.count() / (double)REPS_INSTANTIATE;
  std::cout << "Total for " << REPS_INSTANTIATE << " calls: ";
  std::cout << duration.count() << "(" << per_rep << " s per call)"
            << std::endl;
}

int main(void)
{
  WAVM::Intrinsics::Module* bindings = {WAVM_INTRINSIC_MODULE_REF(env)};
  CallBack sb;
  sb.lib.instantiate(bindings);
  // Warmup
  sb.call_back();
  // Measure remote vs local.
  std::cout << "Measuring callbacks (crossings) vs local (in-sandbox) calls"
            << std::endl;
  std::cout << "Results for " << REPS << " calls" << std::endl;
  measure(sb.call_back, "call_back perf", REPS);
  measure(sb.call_local, "call_local perf", REPS);

  // Measure instantiation cost.
  std::cout << "Measuring instantiation cost" << std::endl;
  measure_instantiate();
  return 0;
}
