cmake_minimum_required(VERSION 2.8)

project(xray)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)  # don't split absolute link paths
    cmake_policy(SET CMP0012 NEW)  # recognize number & boolean literals
    cmake_policy(SET CMP0015 NEW)  # convert relative link paths to absolute
endif(COMMAND cmake_policy)

add_subdirectory(third_party/llvm)

set(XRAY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(XRAY_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
add_subdirectory(lib/core)
