cmake_minimum_required(VERSION 3.6)

project(opencv_demo1)

add_executable(demo main.cpp)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(demo PUBLIC ${OpenCV_LIBS})
