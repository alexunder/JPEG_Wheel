cmake_minimum_required(VERSION 3.0.0)
project(JPEG_Wheel VERSION 0.1.0)

add_definitions(-std=c++11)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set(CMAKE_BUILD_TYPE Debug)

add_executable(JPEG_Wheel src/main.cpp)
