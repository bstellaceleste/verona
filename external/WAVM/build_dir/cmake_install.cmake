# Install script for directory: /opt/verona/external/WAVM

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local64")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/local64/bin/llvm-objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/opt/verona/external/WAVM/Include/WAVM" REGEX "/[^/]*\\.txt$" EXCLUDE REGEX "/[^/]*\\.h\\.in$" EXCLUDE)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/WAVM/Inline" TYPE FILE FILES "/opt/verona/external/WAVM/build_dir/Include/WAVM/Inline/Config.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/WAVM/Inline" TYPE FILE FILES "/opt/verona/external/WAVM/build_dir/Include/WAVM/Inline/Version.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xruntimex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/wavm" TYPE FILE FILES "/opt/verona/external/WAVM/LICENSE.txt")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xruntimex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/wavm/examples" TYPE DIRECTORY FILES "/opt/verona/external/WAVM/Examples/" REGEX "/[^/]*\\.txt$" EXCLUDE)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libWAVM.so.0.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libWAVM.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/opt/verona/external/WAVM/build_dir/libWAVM.so.0.0.0"
    "/opt/verona/external/WAVM/build_dir/libWAVM.so.0"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libWAVM.so.0.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libWAVM.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/local64/bin/llvm-strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libWAVM.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libWAVM.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libWAVM.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/opt/verona/external/WAVM/build_dir/libWAVM.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libWAVM.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libWAVM.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/local64/bin/llvm-strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libWAVM.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/WAVM/WAVMConfig.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/WAVM/WAVMConfig.cmake"
         "/opt/verona/external/WAVM/build_dir/CMakeFiles/Export/lib/cmake/WAVM/WAVMConfig.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/WAVM/WAVMConfig-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/WAVM/WAVMConfig.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/WAVM" TYPE FILE FILES "/opt/verona/external/WAVM/build_dir/CMakeFiles/Export/lib/cmake/WAVM/WAVMConfig.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/WAVM" TYPE FILE FILES "/opt/verona/external/WAVM/build_dir/CMakeFiles/Export/lib/cmake/WAVM/WAVMConfig-relwithdebinfo.cmake")
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/opt/verona/external/WAVM/build_dir/Examples/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/Include/WAVM/Inline/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/Lib/IR/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/Lib/Logging/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/Lib/NFA/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/Lib/Platform/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/Lib/RegExp/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/Lib/VFS/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/Lib/WASM/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/Lib/WASTParse/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/Lib/WASTPrint/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/Programs/wavm/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/Test/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/ThirdParty/BLAKE2/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/ThirdParty/liblmdb/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/Include/WAVM/RuntimeABI/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/Lib/Emscripten/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/Lib/ObjectCache/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/Lib/LLVMJIT/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/Lib/Runtime/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/Lib/ThreadTest/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/Lib/WASI/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/Lib/wavm-c/cmake_install.cmake")
  include("/opt/verona/external/WAVM/build_dir/ThirdParty/libunwind/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/opt/verona/external/WAVM/build_dir/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
