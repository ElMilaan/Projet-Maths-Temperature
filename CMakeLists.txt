cmake_minimum_required(VERSION 3.15)

project(project-temperature)

# file to comile
add_executable(project-temperature src/main.cpp)

# compilation options
target_compile_features(project-temperature PRIVATE cxx_std_11) # use at least c++ 11
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # using GCC
    message(STATUS "compiling with GCC")
    target_compile_options(project-temperature PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors -Wno-unknown-warning-option  -Wno-unused-variable -Wno-comment)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # using Visual Studio C++
    message(STATUS "compiling with MSVC")
    target_compile_options(project-temperature PRIVATE /W3)
endif()
