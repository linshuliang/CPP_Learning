cmake_minimum_required(VERSION 3.6)

# Set a default C++ compile flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add_compile_options
add_compile_options(-Wall -Werror -Wstrict-prototypes -Wmissing-prototypes)

# Set the project name
project(compile_flags)

# Add an executable
add_executable(compile_demo main.cpp)

target_compile_definitions(compile_demo
  PRIVATE
    EX3
)
