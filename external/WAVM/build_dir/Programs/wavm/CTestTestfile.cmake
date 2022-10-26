# CMake generated Testfile for 
# Source directory: /opt/verona/external/WAVM/Programs/wavm
# Build directory: /opt/verona/external/WAVM/build_dir/Programs/wavm
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(HashMap "/opt/verona/external/WAVM/build_dir/bin/wavm" "test" "hashmap")
set_tests_properties(HashMap PROPERTIES  _BACKTRACE_TRIPLES "/opt/verona/external/WAVM/Programs/wavm/CMakeLists.txt;36;add_test;/opt/verona/external/WAVM/Programs/wavm/CMakeLists.txt;0;")
add_test(HashSet "/opt/verona/external/WAVM/build_dir/bin/wavm" "test" "hashset")
set_tests_properties(HashSet PROPERTIES  _BACKTRACE_TRIPLES "/opt/verona/external/WAVM/Programs/wavm/CMakeLists.txt;37;add_test;/opt/verona/external/WAVM/Programs/wavm/CMakeLists.txt;0;")
add_test(I128 "/opt/verona/external/WAVM/build_dir/bin/wavm" "test" "i128")
set_tests_properties(I128 PROPERTIES  _BACKTRACE_TRIPLES "/opt/verona/external/WAVM/Programs/wavm/CMakeLists.txt;38;add_test;/opt/verona/external/WAVM/Programs/wavm/CMakeLists.txt;0;")
add_test(C-API "/opt/verona/external/WAVM/build_dir/bin/wavm" "test" "c-api")
set_tests_properties(C-API PROPERTIES  _BACKTRACE_TRIPLES "/opt/verona/external/WAVM/Programs/wavm/CMakeLists.txt;41;add_test;/opt/verona/external/WAVM/Programs/wavm/CMakeLists.txt;0;")
