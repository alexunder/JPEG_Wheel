cmake_minimum_required(VERSION 3.5)
project(hellotest)

set(CMAKE_CXX_STANDARD 14)

set(INSTALL_GTEST OFF)
add_subdirectory(googletest)

find_package( OpenCV REQUIRED )

add_executable(opencv_test main.cpp opencv_mat_test.cpp)
target_link_libraries(opencv_test gtest  ${OpenCV_LIBS})
