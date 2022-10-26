# CMake generated Testfile for 
# Source directory: /opt/verona/external/WAVM/Test/benchmark
# Build directory: /opt/verona/external/WAVM/build_dir/Test/benchmark
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(benchmark/bitmask.wast "/opt/verona/external/WAVM/build_dir/bin/wavm" "test" "script" "/opt/verona/external/WAVM/Test/benchmark/bitmask.wast" "--trace-assembly" "--enable" "all")
set_tests_properties(benchmark/bitmask.wast PROPERTIES  RUN_SERIAL "TRUE" _BACKTRACE_TRIPLES "/opt/verona/external/WAVM/Test/CMakeLists.txt;17;add_test;/opt/verona/external/WAVM/Test/benchmark/CMakeLists.txt;1;ADD_WAST_TESTS;/opt/verona/external/WAVM/Test/benchmark/CMakeLists.txt;0;")
add_test(benchmark/memory_copy_benchmark.wast "/opt/verona/external/WAVM/build_dir/bin/wavm" "test" "script" "/opt/verona/external/WAVM/Test/benchmark/memory_copy_benchmark.wast" "--trace-assembly" "--enable" "all")
set_tests_properties(benchmark/memory_copy_benchmark.wast PROPERTIES  RUN_SERIAL "TRUE" _BACKTRACE_TRIPLES "/opt/verona/external/WAVM/Test/CMakeLists.txt;17;add_test;/opt/verona/external/WAVM/Test/benchmark/CMakeLists.txt;1;ADD_WAST_TESTS;/opt/verona/external/WAVM/Test/benchmark/CMakeLists.txt;0;")
add_test(benchmark/interleaved_load_store_benchmark.wast "/opt/verona/external/WAVM/build_dir/bin/wavm" "test" "script" "/opt/verona/external/WAVM/Test/benchmark/interleaved_load_store_benchmark.wast" "--trace-assembly" "--enable" "all")
set_tests_properties(benchmark/interleaved_load_store_benchmark.wast PROPERTIES  RUN_SERIAL "TRUE" _BACKTRACE_TRIPLES "/opt/verona/external/WAVM/Test/CMakeLists.txt;17;add_test;/opt/verona/external/WAVM/Test/benchmark/CMakeLists.txt;1;ADD_WAST_TESTS;/opt/verona/external/WAVM/Test/benchmark/CMakeLists.txt;0;")
