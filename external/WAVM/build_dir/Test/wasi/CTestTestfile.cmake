# CMake generated Testfile for 
# Source directory: /opt/verona/external/WAVM/Test/wasi
# Build directory: /opt/verona/external/WAVM/build_dir/Test/wasi
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(wasi_args "/opt/verona/external/WAVM/build_dir/bin/wavm" "run" "--abi=wasi" "/opt/verona/external/WAVM/Test/wasi/args.wasm" "arg1" "arg2")
set_tests_properties(wasi_args PROPERTIES  PASS_REGULAR_EXPRESSION "argc=3
argv\\[0\\]: .+
argv\\[1\\]: arg1
argv\\[2\\]: arg2
argv\\[3\\]: <null>" _BACKTRACE_TRIPLES "/opt/verona/external/WAVM/Test/wasi/CMakeLists.txt;36;add_test;/opt/verona/external/WAVM/Test/wasi/CMakeLists.txt;0;")
add_test(wasi_clock "/opt/verona/external/WAVM/build_dir/bin/wavm" "run" "--abi=wasi" "/opt/verona/external/WAVM/Test/wasi/clock.wasm")
set_tests_properties(wasi_clock PROPERTIES  _BACKTRACE_TRIPLES "/opt/verona/external/WAVM/Test/wasi/CMakeLists.txt;42;add_test;/opt/verona/external/WAVM/Test/wasi/CMakeLists.txt;0;")
add_test(wasi_exit "/opt/verona/external/WAVM/build_dir/bin/wavm" "run" "--abi=wasi" "/opt/verona/external/WAVM/Test/wasi/exit.wasm")
set_tests_properties(wasi_exit PROPERTIES  _BACKTRACE_TRIPLES "/opt/verona/external/WAVM/Test/wasi/CMakeLists.txt;46;add_test;/opt/verona/external/WAVM/Test/wasi/CMakeLists.txt;0;")
add_test(wasi_random "/opt/verona/external/WAVM/build_dir/bin/wavm" "run" "--abi=wasi" "/opt/verona/external/WAVM/Test/wasi/random.wasm")
set_tests_properties(wasi_random PROPERTIES  _BACKTRACE_TRIPLES "/opt/verona/external/WAVM/Test/wasi/CMakeLists.txt;50;add_test;/opt/verona/external/WAVM/Test/wasi/CMakeLists.txt;0;")
add_test(wasi_stdout "/opt/verona/external/WAVM/build_dir/bin/wavm" "run" "--abi=wasi" "/opt/verona/external/WAVM/Test/wasi/stdout.wasm")
set_tests_properties(wasi_stdout PROPERTIES  PASS_REGULAR_EXPRESSION "Hello world!" _BACKTRACE_TRIPLES "/opt/verona/external/WAVM/Test/wasi/CMakeLists.txt;54;add_test;/opt/verona/external/WAVM/Test/wasi/CMakeLists.txt;0;")
add_test(wasi_stdout_detected_abi "/opt/verona/external/WAVM/build_dir/bin/wavm" "run" "/opt/verona/external/WAVM/Test/wasi/stdout.wasm")
set_tests_properties(wasi_stdout_detected_abi PROPERTIES  PASS_REGULAR_EXPRESSION "Hello world!" _BACKTRACE_TRIPLES "/opt/verona/external/WAVM/Test/wasi/CMakeLists.txt;60;add_test;/opt/verona/external/WAVM/Test/wasi/CMakeLists.txt;0;")
