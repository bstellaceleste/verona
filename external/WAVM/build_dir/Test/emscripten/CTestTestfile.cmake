# CMake generated Testfile for 
# Source directory: /opt/verona/external/WAVM/Test/emscripten
# Build directory: /opt/verona/external/WAVM/build_dir/Test/emscripten
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(emscripten_args "/opt/verona/external/WAVM/build_dir/bin/wavm" "run" "--abi=emscripten" "/opt/verona/external/WAVM/Test/emscripten/args.wasm" "arg1" "arg2")
set_tests_properties(emscripten_args PROPERTIES  PASS_REGULAR_EXPRESSION "argc=3
argv\\[0\\]: .+
argv\\[1\\]: arg1
argv\\[2\\]: arg2
argv\\[3\\]: <null>" _BACKTRACE_TRIPLES "/opt/verona/external/WAVM/Test/emscripten/CMakeLists.txt;14;add_test;/opt/verona/external/WAVM/Test/emscripten/CMakeLists.txt;0;")
add_test(emscripten_clock "/opt/verona/external/WAVM/build_dir/bin/wavm" "run" "--abi=emscripten" "/opt/verona/external/WAVM/Test/emscripten/clock.wasm")
set_tests_properties(emscripten_clock PROPERTIES  _BACKTRACE_TRIPLES "/opt/verona/external/WAVM/Test/emscripten/CMakeLists.txt;20;add_test;/opt/verona/external/WAVM/Test/emscripten/CMakeLists.txt;0;")
add_test(emscripten_exit "/opt/verona/external/WAVM/build_dir/bin/wavm" "run" "--abi=emscripten" "/opt/verona/external/WAVM/Test/emscripten/exit.wasm")
set_tests_properties(emscripten_exit PROPERTIES  _BACKTRACE_TRIPLES "/opt/verona/external/WAVM/Test/emscripten/CMakeLists.txt;24;add_test;/opt/verona/external/WAVM/Test/emscripten/CMakeLists.txt;0;")
add_test(emscripten_stdout "/opt/verona/external/WAVM/build_dir/bin/wavm" "run" "--abi=emscripten" "/opt/verona/external/WAVM/Test/emscripten/stdout.wasm")
set_tests_properties(emscripten_stdout PROPERTIES  PASS_REGULAR_EXPRESSION "Hello world!" _BACKTRACE_TRIPLES "/opt/verona/external/WAVM/Test/emscripten/CMakeLists.txt;28;add_test;/opt/verona/external/WAVM/Test/emscripten/CMakeLists.txt;0;")
add_test(emscripten_stdout_detected_abi "/opt/verona/external/WAVM/build_dir/bin/wavm" "run" "/opt/verona/external/WAVM/Test/emscripten/stdout.wasm")
set_tests_properties(emscripten_stdout_detected_abi PROPERTIES  PASS_REGULAR_EXPRESSION "Hello world!" _BACKTRACE_TRIPLES "/opt/verona/external/WAVM/Test/emscripten/CMakeLists.txt;34;add_test;/opt/verona/external/WAVM/Test/emscripten/CMakeLists.txt;0;")
