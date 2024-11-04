cmake_minimum_required(VERSION 3.13)


# give a name to the project
project(project-temperature)

# include Eigen
find_package(Eigen3 REQUIRED)
if(${EIGEN3_FOUND})
    message(STATUS "lib EIGEN3 found")
    message(STATUS "  version " ${EIGEN3_VERSION_STRING})
    message(STATUS "  include " ${EIGEN3_INCLUDE_DIR})
else()
    message(FATAL_ERROR "lib EIGEN3 not found")
endif()


# files to compile
add_executable(project-temperature src/main.cpp src/fileSC.cpp src/fenetre.cpp src/radiateur.cpp src/scene.cpp src/source.cpp src/temperature.cpp)

# compilation options
target_compile_features(project-temperature PRIVATE cxx_std_11) # use at least c++ 11
if (MSVC)
    target_compile_options(project-temperature PRIVATE /W3)
else()
    target_compile_options(project-temperature PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors)
endif()

# lib include path
target_include_directories(project-temperature PRIVATE "${EIGEN3_INCLUDE_DIR}")