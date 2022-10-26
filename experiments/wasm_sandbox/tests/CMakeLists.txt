cmake_minimum_required(VERSION 3.8.0)
project(wasmsandbox-tests LANGUAGES C CXX)
SET(SANDBOX_TESTS
  basic-adder 
  measure
  )

set(WASM_CXX "/opt/wasi-sdk/bin/clang++" CACHE STRING "Path to the wasi clang++ compiler")
set(DEFAULT_WASI_ALLOC false)
set(USE_DEFAULT_WASI_ALLOC ${DEFAULT_WASI_ALLOC} CACHE BOOL "Use WASI malloc.")

function(compile_sandbox TEST_LIB_SRC, TEST_LIB_NAME)
  set(WASM_FLAGS -fno-exceptions -Wl,--no-entry  -Wl,--allow-undefined -mexec-model=reactor -std=c++20)
  set(SDBLIB -I${CMAKE_CURRENT_SOURCE_DIR}/../include/)
  set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_LIB_SRC})
  set(TGT ${CMAKE_CURRENT_BINARY_DIR}/${TEST_LIB_NAME})
	set(SYSROOT --sysroot=${CMAKE_SOURCE_DIR}/wasi-sysroot)
  if(USE_DEFAULT_WASI_ALLOC)
    message(STATUS "Using regular wasi malloc implementation")
    set(SYSROOT )
  endif()
  add_custom_target(
    WASM_${TEST_LIB_NAME} ALL
		COMMAND ${WASM_CXX} ${WASM_FLAGS} ${SYSROOT} ${SDBLIB} ${SRC} -o ${TGT}
    BYPRODUCTS $${CMAKE_CURRENT_BINARY_DIR}/${TEST_LIB_NAME}
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_LIB_SRC}
    )
endfunction()

foreach(TEST_NAME ${SANDBOX_TESTS})
  set(TEST_EXE_SRC "sandbox-${TEST_NAME}.cc")
  set(TEST_LIB_SRC "sandboxlib-${TEST_NAME}.cc")
  set(TEST_LIB_NAME "sandboxed-${TEST_NAME}.wasm")
  set(TEST_NAME "test-sandbox-${TEST_NAME}")
  add_executable(${TEST_NAME} ${TEST_EXE_SRC})
	set_target_properties(${TEST_NAME} PROPERTIES
		INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/include/;${CMAKE_SOURCE_DIR}/../../external/snmalloc/src"
	)
#  set_target_properties(${TEST_NAME} PROPERTIES 
#    INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/include"
#    )
  target_link_libraries(${TEST_NAME} wasmsandbox)
  target_compile_definitions(${TEST_NAME} PRIVATE SANDBOX_LIBRARY=\"${CMAKE_CURRENT_BINARY_DIR}/${TEST_LIB_NAME}\")
  compile_sandbox(${TEST_LIB_SRC} ${TEST_LIB_NAME})
endforeach()
