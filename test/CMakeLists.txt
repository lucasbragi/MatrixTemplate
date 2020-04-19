cmake_minimum_required(VERSION 3.15)
add_subdirectory(lib/googletest-master)
set(gtest_SOURCE_DIR, lib/googletest-master/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


set(SOURCE_FILES runAllTest.cpp)
add_executable(TestMatrix runAllTest.cpp test.cpp)
target_link_libraries(TestMatrix gtest gtest_main core)