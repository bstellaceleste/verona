cmake_minimum_required(VERSION 3.8.0)
set(CMAKE_CXX_STANDARD 20)
project(wasm-sandbox LANGUAGES C CXX)

set(LIBWASMSANDBOX_SOURCES src/libwasmsandbox.cc)

include_directories(AFTER "${CMAKE_SOURCE_DIR}/../../external/snmalloc/src")
include_directories(BEFORE "${CMAKE_SOURCE_DIR}/include")

# Enable WASI default malloc implementation (off by default).
set(DEFAULT_WASI_ALLOC false)
set(USE_DEFAULT_WASI_ALLOC ${DEFAULT_WASI_ALLOC} CACHE BOOL "Use WASI malloc.")

add_compile_options(-mcx16)

# Our main target.
add_library(wasmsandbox SHARED ${LIBWASMSANDBOX_SOURCES})
if (USE_DEFAULT_WASI_ALLOC)
   message(STATUS "Using default wasi allocator")
   add_definitions(-DWASI_ALLOCATOR)
endif()

add_subdirectory(
  ${CMAKE_CURRENT_SOURCE_DIR}/../../external/WAVM
  ${CMAKE_CURRENT_BINARY_DIR}/WAVM)
target_link_libraries(wasmsandbox libWAVM)
#add_subdirectory(
#  ${CMAKE_CURRENT_SOURCE_DIR}/../../external/snmalloc/
#  ${CMAKE_CURRENT_BINARY_DIR}/snmalloc)
#target_link_libraries(wasmsandbox snmalloc)
#
add_subdirectory(tests)
