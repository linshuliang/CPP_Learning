# 查找当前目录下所有的源文件
# 将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

# 指定生成链接库
add_library(MathFunctions ${DIR_LIB_SRCS})

