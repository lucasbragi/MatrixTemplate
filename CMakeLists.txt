cmake_minimum_required(VERSION 3.15)
project(untitled4)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES main.cpp)
add_executable(untitled4 main.cpp Matrix.h cmake-build-debug/Tests/test.cpp MatrixFactory.h)
target_link_libraries(untitled4 gtest gtest_main)