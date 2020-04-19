cmake_minimum_required(VERSION 3.15)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)


set(SOURCE_FILES runAllTest.cpp)
add_executable(TestMatrix runAllTest.cpp test.cpp)
target_link_libraries(TestMatrix gtest gtest_main)