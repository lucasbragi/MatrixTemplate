cmake_minimum_required(VERSION 3.15)
project(untitled4)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(test)

set(SOURCE_FILES main.cpp)
add_executable(untitled4 main.cpp Matrix.h MatrixFactory.h)
add_library(core ${SOURCE_FILES})
set_target_properties(core PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(untitled4 core)