# 指定最低版本要求
cmake_minimum_required(VERSION 3.6)

# 设定项目名称
project (dynamicLibrary)

# 生成一个动态库, 命名为 hello_library
add_library(hello_library SHARED src/Hello.cpp)

# 可以用 ALIAS 关键字，来定义动态库的别名
add_library(hello::library ALIAS hello_library)

# 指定头文件的搜索路径
# target_include_directories can not be used on an ALIAS target.
target_include_directories(hello_library
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include)

# 创建一个可执行文件
add_executable(hello_binary src/main.cpp)

# 链接动态库和可执行文件
target_link_libraries(hello_binary
  PRIVATE
    hello::library
)

