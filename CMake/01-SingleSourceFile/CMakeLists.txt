# 指定运行此配置文件所需的 CMake 的最低版本
cmake_minimum_required (VERSION 3.6)

# 该命令表示项目的名称是 Demo1
project (Demo1)

# 将名为 cmath_pow.cc 的源文件编译成一个名称为 Demo 的可执行文件。
add_executable(Demo cmath_pow.cc)

# 在当前目录执行 `cmake .` 
# 得到 Makefile 后再使用 `make` 命令编译得到 Demo1 可执行文件。
