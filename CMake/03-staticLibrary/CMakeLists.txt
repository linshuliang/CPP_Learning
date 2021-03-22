# 指定运行此配置文件所需的 CMake 的最低版本
cmake_minimum_required(VERSION 3.6)

# 指定项目名称
project (hello_static_library)

# 生成一个静态库，名为 hello.lib
add_library(hello
  STATIC
    src/Hello.cpp
  )

# 指定编译 hello 文件时，头文件的搜索路径
target_include_directories(hello
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
  )

# 创建一个可执行文件 hello_binary.exe
add_executable(hello_binary src/main.cpp)

# 链接可执行文件 hello_binary.exe 和库 hello.lib
target_link_libraries(hello_binary
  PRIVATE
    hello
)

