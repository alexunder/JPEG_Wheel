cmake_minimum_required(VERSION 3.5)
project(jpeg_test)

set(CMAKE_CXX_STANDARD 14)


set(INSTALL_GTEST OFF)
add_subdirectory(googletest)

include_directories("../src")

add_executable(jpeg_test main.cpp bitmap_test.cpp)
target_link_libraries(jpeg_test gtest)