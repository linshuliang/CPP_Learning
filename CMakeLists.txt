cmake_minimum_required (VERSION 3.6)

project(CPP_LEARNING)

set (CMAKE_CXX_STANDARD 11)

# 设置可执行文件的输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

add_subdirectory(src)