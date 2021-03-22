# CMake 最低版本要求
cmake_minimum_required(VERSION 3.6)

# 项目名称为 Demo4
project (Demo4)

# 是否使用自己的 MathFunctions 库
option(USE_MYMATH "Use provided math implementation." ON)

# 加入一个配置头文件，用 *.h.in 文件来生成 *.h 文件
# 进而处理 CMake 对源码的设置
configure_file(
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_SOURCE_DIR}/config.h"
	)

if(USE_MYMATH)
  include_directories("${PROJECT_SOURCE_DIR}/math")
  # 添加 math 子目录
  add_subdirectory("math")
  set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

# 查找当前目录中的所有源文件
# 并将结果保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(Demo ${DIR_SRCS})

# 添加链接库
target_link_libraries(Demo PUBLIC ${EXTRA_LIBS})

