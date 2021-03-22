# 指定运行此配置文件所需的 CMake 的最低版本
cmake_minimum_required(VERSION 3.6)

# 设置 PROJECT 名称
project (hello_headers)

# 给变量赋值
set(SOURCES src/Hello.cpp src/main.cpp)

# 将源文件编译为可执行文件
add_executable(hello_headers ${SOURCES})

# Set the directories that should be included in the build command for this target.
# when running g++, these will be included as -I/directory/path
target_include_directories(hello_headers
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
