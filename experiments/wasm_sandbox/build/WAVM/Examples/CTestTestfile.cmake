# CMake generated Testfile for 
# Source directory: /opt/verona/external/WAVM/Examples
# Build directory: /opt/verona/external/WAVM/build_dir/Examples
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(examples_zlib "/opt/verona/external/WAVM/build_dir/bin/wavm" "run" "/opt/verona/external/WAVM/Examples/zlib.wasm")
set_tests_properties(examples_zlib PROPERTIES  PASS_REGULAR_EXPRESSION "sizes: 100000,25906
ok." _BACKTRACE_TRIPLES "/opt/verona/external/WAVM/Examples/CMakeLists.txt;12;add_test;/opt/verona/external/WAVM/Examples/CMakeLists.txt;0;")
