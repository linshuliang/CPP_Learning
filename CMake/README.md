# CMake

## 简介

CMake是一个跨平台的安装（[编译](https://baike.baidu.com/item/编译/1258343)）工具，可以用简单的语句来描述所有平台的安装(编译过程)。能够输出各种各样的 `makefile`或者`project`文件，能测试编译器所支持的C++特性，类似UNIX下的automake。只是 CMake 的文件名为`CMakeLists.txt`。cmake 并不直接构建出最终的软件，而是产生标准的构建档（如 Unix 的 Makefile 或 Windows Visual C++ 的 projects/workspaces），然后再依一般的建构方式使用。这使得熟悉某个IDE的开发者可以用标准的方式建构软件。



## gcc 选项

| 命令描述     | 作用                                                         |
| ------------ | ------------------------------------------------------------ |
| -l *library* | 进行链接时搜索名为 *library* 的库。                          |
| -I *dir*     | 把 *dir* 加入到头文件的搜索路径列表中。                      |
| -L *dir*     | 把 *dir* 加入到搜索库文件的路径列表中。                      |
| -O0          | 禁止编译器进行优化。默认为此项。                             |
| -O1          | 使用能**减少目标文件大小以及执行时间**并且不会使编译时间明显增加的优化。在编译大型程序的时候会显著增加编译时内存的使用。 |
| -O2          | 包含 `-O1` 的优化，并增加了不需要在目标文件大小和执行速度上进行折衷的优化，编译器不执行循环展开以及函数内联。此选项将增加编译时间和目标文件的执行性能。 |
| -O3          | 打开 `-O2` 的所有优化选项并且增加 `-finline-functions`, `-funswitch-loops`, `-fpredictive-commoning` , `-fgcse-after-reload`, `-ftree-vectorize` 优化选项。 |
| -Os          | 专门优化目标文件大小，执行所有不增加目标文件大小的 `-O2` 优化选项，并且执行专门减小目标文件大小的优化选项。 |
| -o           | 指定目标名称，缺省的时候，gcc 编译出来的文件是 a.out         |
| -g           | 生成操作系统本地格式的调试信息。                             |
| -static      | 此选项将禁止使用动态库，所以，编译出来的文件一般都很大，也不需要什么动态链接库，就可以运行。 |
| -share       | 此选项将尽量使用动态库，所以生成文件比较小，但是需要系统包含动态库。 |
| -Wall        | 会打开一些很有用的警告选项，建议编译时加此选项。             |



## CMake Variables

Variables are the basic unit of storage in the CMake Language. Their values are always of string type, though some commands may interpret the strings as values of other types.

The [`set()`](https://cmake.org/cmake/help/v3.6/command/set.html#command:set) and [`unset()`](https://cmake.org/cmake/help/v3.6/command/unset.html#command:unset) commands explicitly set or unset a variable, but other commands have semantics that modify variables as well. 

变量名是区分大小写的，建议坚持使用仅由 **字符，数字， `_`，`-`** 组成的名称。

普通变量和缓存条目的范围和相互作用（The scopes and interaction of normal variables and cache entries），可参考下面的 set 命令。



## CMake 命令

`CMakeLists.txt` 的语法比较简单，由命令、注释和空格组成，其中命令是不区分大小写的。符号 `#` 后面的内容被认为是注释。

命令由命令名称、小括号和参数组成，参数之间使用空格进行间隔。

| cmake 函数                                                   | 作用                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `cmake_minimum_required(VERSION *.*)`                        | 指定运行此配置文件所需的 CMake 的最低版本。                  |
| `project(<project_name>)`                                    | 指明项目的名称。the `project()` function, will create a variable `${PROJECT_NAME}` with the given value. |
| [add_executable](https://cmake.org/cmake/help/v3.6/command/add_executable.html) | 将源文件编译成可执行文件。                                   |
| [aux_source_directory(<dir> <variable>)](https://cmake.org/cmake/help/v3.6/command/aux_source_directory.html) | 收集指定目录`<dir>`中所有源文件的名称，并将名称列表存进指定变量`<variable>` 。 |
| [add_subdirectory(source_dir [binary_dir])](https://cmake.org/cmake/help/v3.6/command/add_subdirectory.html) | 在构建中添加一个子目录 `source_dir`。                        |
| [add_library](https://cmake.org/cmake/help/v3.6/command/add_library.html) | 将指定的源文件编译为链接库。                                 |
| [add_compile_options](https://cmake.org/cmake/help/v3.6/command/add_compile_options.html) | 将选项添加到源文件的编译选项。                               |
| [add_definitions](https://cmake.org/cmake/help/v3.6/command/add_definitions.html) | 将选项添加到源文件的编译定义。                               |
| [set](https://cmake.org/cmake/help/v3.6/command/set.html)    | 将普通变量，缓存变量或环境变量设置为给定值。                 |
| [set_property](https://cmake.org/cmake/help/v3.6/command/set_property.html) | 在给定范围内设置命名属性。                                   |
| [target_link_libraries](https://cmake.org/cmake/help/v3.6/command/target_link_libraries.html?highlight=target_link_libraries) | 为目标指定链接库。                                           |
| [target_include_directories](https://cmake.org/cmake/help/v3.6/command/target_include_directories.html) | 为目标指明头文件的搜索路径。                                 |
| [target_compile_definitions](https://cmake.org/cmake/help/v3.6/command/target_compile_definitions.html) | 给目标添加编译定义。                                         |
| [target_compile_options](https://cmake.org/cmake/help/v3.6/command/target_compile_options.html) | 给目标添加编译选项。                                         |
| [link_libraries](https://cmake.org/cmake/help/v3.6/command/link_libraries.html) | 将库链接到后续添加的所有目标。                               |
| [include_directories](https://cmake.org/cmake/help/v3.6/command/include_directories.html) | 新增头文件的搜索目录。                                       |
| [link_directories](https://cmake.org/cmake/help/v3.6/command/link_directories.html) | 新增链接库的搜索目录。                                       |
| `option(<option_variable> "help string describing option" [initial value])` | Provide an option for the user to select as `ON` or `OFF`. If no initial value is provided, `OFF` is used. If the option is already set as a normal variable then the command does nothing. |
| message                                                      | Display a message to user.                                   |

### 命令详解

#### add_executable

```cmake
add_executable(<name> source1 [source2 ...])
```

将 `源文件(source1 [source2 ...])` 编译成可执行文件 `<name>`，可执行文件的名称必须是唯一的，不能重复。



#### aux_source_directory

```cmake
aux_source_directory(<dir> <variable>)
```

Collects the names of all the source files in the specified directory `<dir>` and stores the list in the `<variable>` provided. 



#### add_subdirectory

```cmake
add_subdirectory(source_dir [binary_dir])
```

在构建中添加一个子目录`source_dir`。

**参数说明：**

* `source_dir` : 指定源 CMakeLists.txt 和代码文件所在的目录；
* `binary_dir` : 指定放置输出文件的目录。



#### add_library

添加一个库到工程中，指定这个库的源文件。

```cmake
add_library(<name> [STATIC | SHARED | MODULE]
            [EXCLUDE_FROM_ALL]
            source1 [source2 ...])
```

`<name>`是目标库的名字，这个名字在工程内全局唯一，最终编译出来的目标文件名字取决于目标平台（比如说`lib<name>.a`，`<name>.lib` ，`<name>.dll`）

`STATIC`, `SHARED`, 或`MODULE`用来指定要创建的库的类型。

- `STATIC`，静态链接库，供链接其他目标时使用。`STATIC` libraries are archives of object files for use when linking other targets.
- `SHARED`，动态链接库，运行时加载。`SHARED` libraries are linked dynamically and loaded at runtime.
- `MODULE`，未链接到其他目标的插件，但可以在运行时使用类似`dlopen-like`的功能动态加载。 Module libraries are plugins that are not linked into other targets but may be loaded dynamically at runtime using dlopen-like functionality.

`EXCLUDE_FROM_ALL` 会在目标文件上设置相应的属性（执行默认make的时候，这个目标文件会被排除在外，不被编译）。



```cmake
add_library(<name> ALIAS <target>)
```

创建链接库`<target>`的别名`<name>`，从而后续的命令可用 `<name>` 来引用 `<target>`。



#### set

* Set Normal Variable

```cmake
set(<variable> <value1> [<value2> ...])
```

普通变量相当于C++中的局部变量，这种变量不能跨越 CMakeLists.txt 文件。和编程语言中局部变量的用法类似，新定义普通变量会屏蔽CMake缓存中的同名变量，（类似局部变量屏蔽全局变量），但是这条语句不会改变缓存中的`<variable>`变量。

* Set Cache Entry

```cmake
set(<variable> <value1> [<value2> ...] CACHE <type> <docstring> [FORCE])
```

Set the given cache `<variable>` (cache entry). Since cache entries are meant to provide user-settable values, this does not overwrite existing cache entries by default. Use the `FORCE` option to overwrite existing entries.

设置给定的高速缓存变量 `<variable>`，由于高速缓存条目旨在提供用户可设置的值，因此默认情况下不会覆盖现有的高速缓存条目。可以使用关键字`FORCE`来覆盖现有条目。



`CACHE`关键字的作用：

* 如果缓存中不存在同名的变量，则将这个变量写入缓存并使用；
* 如果缓存中存在同名的变量，根据FORCE来决定是否写入缓存：
  * 如果没有 FORCE，这条语句不起作用，使用缓存中的变量；
  * 如果有 FORCE，使用当前设置的值。
  * 如果是FORCE，也能修改-D选项设置的CACHE变量，所以传入的命令选项由可能是无效的。
* 缓存变量也可以设置为只在本文件内生效，将 STRING 类型改为 INTERNAL 即可。



`<type>` 必须为以下值之一：

| <type>   | 含义                                                         |
| -------- | ------------------------------------------------------------ |
| BOOL     | 布尔值，ON/OFF                                               |
| FILEPATH | 文件路径 (Path to a file on disk)                            |
| PATH     | 目录路径 (Path to a directory on disk)                       |
| STRING   | 一行文字 (A line of text)                                    |
| INTERNAL | 一行文字 (A line of text)，Use of this type implies `FORCE`. |

* Set Environment Variable

```cmake
set(ENV{<variable>} <value> ...)
```

Set the current process environment `<variable>` to the given value.



**总结**

* 如果项目有多层目录，有需要跨文本的变量应该使用`CACHE`类型；
* 如果只是当前文本的变量，则不需要使用 `CACHE`；
* 尽量避免使用同名的普通变量和缓存变量；
* 由于CMake 没有清除缓存的方法，如果要彻底清除缓存，需要删除 build 或 release 文件夹中的所有文件。



#### target_include_directories

When you have different include folders, you can make your compiler aware of them using the `target_include_directories()`. When compiling this target this will add these directories to the compiler with the `-I` flag e.g. `-I/directory/path`.

```cmake
target_include_directories(<target> [SYSTEM] [BEFORE]
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
```

指定编译 `<target>` 文件时，头文件的搜索路径。 `<target>` 必须是一个已经通过诸如 `add_executable()`或者`add_library()`函数创建了的目标，并且不是一个标注成 `IMPORTED` 的目标。



各个作用域标识符的含义为：

* PRIVATE : 属性只应用到本目标，不应用到链接本目标的目标。
* PUBLIC : 属性既应用到本目标也应用到链接此目标的目标。

* INTERFACE ：属性不应用到本目标，应用到链接本目标的目标。



#### target_link_libraries

指定链接目标及其依赖项要使用的库(libraries)或标志(flags)。

```cmake
target_link_libraries(<target>
                      <PRIVATE|PUBLIC|INTERFACE> <item>...
                      [<PRIVATE|PUBLIC|INTERFACE> <item>...]...)
```



#### target_compile_definitions

```cmake
target_compile_definitions(<target>
	<INTERFACE|PUBLIC|PRIVATE> [items ...]
	[<INTERFACE|PUBLIC|PRIVATE>] [items ...])
```

为目标添加编译选项。



#### link_libraries

```cmake
link_libraries(lib1 [lib2 ...])
```

新增链接库。



### link_directories

新增链接库的搜索路径。

```cmake
link_directories(directory1 [directory2 ...])
```



### include_directories

新增头文件的搜索路径。

```cmake
include_directories(dir1 [dir2 ...])
```



### find_package

`find_package` 用于加载外部项目的设置。

```cmake
find_package(<package> )
```



#### 以 OpenCV 为例讲解 find_package

```
./OpenCV_Demo
    |
    +--- main.cc
    |
    +--- CMakeLists.txt
```

CMakeLists.txt 文件：

```cmake
cmake_minimum_required(VERSION 3.6)
  
project(opencv_demo1)

add_executable(demo main.cpp)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

link_directories(${OpenCV_LIBRARY_DIRS})

target_link_libraries(demo PUBLIC ${OpenCV_LIBS})
```

main.cpp 文件：

```c++
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
    //读取原始图像
    string im_path = "../data/apple.jpeg";
    Mat in_image = imread(im_path, IMREAD_UNCHANGED);

    if (in_image.empty()) {
        //检查是否读取图像
        cout << "Error! Input image cannot be read...\n";
        return -1;
    }

    //创建两个具有图像名称的窗口
    namedWindow("Input", WINDOW_AUTOSIZE);
    namedWindow("Output", WINDOW_AUTOSIZE);

    //在之前创建的窗口中显示图片
    imshow("Input", in_image);

    Mat out_image;
    cvtColor(in_image, out_image, COLOR_BGR2GRAY);
    imshow("Output", in_image);

    cout << "Press any key to exit...\n";
    waitKey(); // Wait for key press

    // 写入图像
    imwrite("../data/output.jpeg", out_image);
    return 0;
}
```

工作流程如下：

* `find_package`在一些目录中查找OpenCV的配置文件。
* 当找到 OpenCV 程序库后，会帮助我们预定义几个文件：
  * OpenCV_FOUND : 是否找到 OpenCV；
  * OpenCV_INCLUDE_DIRS : OpenCV 的头文件目录；
  * OpenCV_LIBRARY_DIRS : OpenCV 的库文件目录；
  * OpenCV_LIBS : OpenCV 所有的库文件列表。 
* 设置头文件目录/库文件目录的搜索路径，链接库文件。



## 编译器和工具（Compilers and Tools)

CMake has a number of built in build configurations which can be used to compile your project. These specify the optimization levels and if debug information to be included in the binary.

CMake will create by default the following variables when using a **single-configuration** generator:

* None : 编译器预设值。

* Release : Adds the `-O3 -DNDEBUG` flags to the compiler. 执行速度最佳化。
* Debug : Adds the `-g` flag，产生报错信息。
* MinSizeRel : Adds `-Os -DNDEBUG`.  最小化目标文件。
* RelWithDebInfo : Adds `-O2 -g -DNDEBUG`.  执行速度最佳化，但仍然会启用 `debug flag`。



可以在命令行中传入参数`-DCMAKE_BUILD_TYPE`，来指定编译选项：

```shell
cmake .. -DCMAKE_BUILD_TYPE=Release
```

也可以在 CMakeLists.txt 中指定编译选项：

| CMake 内置变量名称        | 含义                                                         |
| ------------------------- | ------------------------------------------------------------ |
| BUILD_SHARED_LIBS         | if this is set to `ON`, then all libraries are built as shared libraries by default. |
| CMAKE_BUILD_TYPE          | 指定编译组态。A variable which controls the type of build when using a *single-configuration generator* like the Makefile generator. It is case-insensitive. |
| CMAKE_CONFIGURATION_TYPES | 当使用多配置生成器（例如Visual Studio的生成器）时，此变量包含可用配置的列表。When using a *multi-configuration generator*, such as the one for **Visual Studio**, this variable contains a list of the available configurations. |
| CMAKE_C_COMPILER          | 指定**C编译器**，通常，CMake运行时能够自动检测C语言编译器。进行嵌入式系统开发时，通常需要设置此变量，指定交叉编译器。 |
| CMAKE_CXX_COMPILER        | 指定**C++编译器**。                                          |
| CMAKE_C_FLAGS             | 指定编译C文件的编译选项，比如`-g`指定产生调试信息。也可以通过`add_definitions`命令添加编译选项。 |
| CMAKE_CXX_FLAGS           | 指定编译C++文件的编译选项，除此之外，也可以使用 `ADD_COMPILE_OPTIONS()` 来指定。 |
| CMAKE_C_OUTPUT_EXTENSION  | C 目标文件的后缀名，通常为 .o 或者 .obj                      |
| EXECUTABLE_OUTPUT_PATH    | 指定**可执行文件的存放路径**。                               |
| LIBRARY_OUTPUT_PATH       | 指定**库文件的存放路径**。                                   |



### 指定 C++ 标准

在 CMake 中启用对特定 C++ 标准的支持最简单的方法是使用 `CMAKE_CXX_STANDARD`，并将 `CMAKE_CXX_STANDARD_REQUIRED`设为`True`。

```cmake
# specify the C++ Standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
```



### 指定编译选项的三种方法

* `add_compile_option()` 函数
* `add_definitions()` 函数
* `set()`函数修改 `CMAKE_CXX_FLAGS` 或 `CMAKE_C_FLAGS`



**例1：** 添加编译选项

```cmake
# add_compile_options
add_compile_options(-Wall -Werror -Wstrict-prototypes -Wmissing-prototypes)

# add_definitions
add_definitions(-Wall -Werror -Wstrict-prototypes -Wmissing-prototypes)

# set
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wstrict-prototypes -Wmissing-prototypes")

# 上面三种方式在有的情况下效果是一样的，但请注意它们还是有区别的：
# add_compile_options命令和add_definitions添加的编译选项是针对所有编译器的(包括c和c++编译器)，
# set命令设置 CMAKE_C_FLAGS 或 CMAKE_CXX_FLAGS 变量则是分别只针对c编译器和c++编译器。
```

**例2：**在编译选项中加入 c++11 支持

```cmake
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
```



### CMake 的内置变量

CMake syntax specifies a number of [variables](https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/Useful-Variables) which can be used to help find useful directories in your project or source tree. Some of these include:

#### 基本变量

| CMake 内置变量名称 | 含义                            |
| ------------------ | ------------------------------- |
| PROJECT_NAME       | 项目名称，由`project()`函数指定 |
| CMAKE_PROJECT_NAME | 由设置的第一个项目的名称        |

#### 目录路径

| CMake 内置变量名称       | 含义                                                         |
| ------------------------ | ------------------------------------------------------------ |
| PROJECT_SOURCE_DIR       | Contains the full path to the root of your project source directory, i.e. to the nearest directory where CMakeLists.txt contains the `project()` command。工程的顶层目录。 |
| PROJECT_BINARY_DIR       | Contains the full path to the top level directory of your build tree。工程的 build 目录。如果是 In-Place Build，则与 PROJECT_SOURCE_DIR 相同；如果是 Out-of-Source Build，则指的是工程编译发生的目录。 |
| CMAKE_SOURCE_DIR         | the name of the first project set by the `project()` command, i.e. the top level project. 与 PROJECT_SOURCE_DIR 相同。 |
| CMAKE_BINARY_DIR         | If you are building in-source, this is the same as CMAKE_SOURCE_DIR, otherwise this is the top level directory of your build tree。 与`PROJECT_BINARY_DIR`相同。 |
| CMAKE_CURRENT_SOURCE_DIR | This is the directory where the currently processed CMakeLists.txt is located in. 调用这个变量的 CMakeLists.txt 的所在目录。 |
| CMAKE_CURRENT_BINARY_DIR | If you are building in-source, this is the same as CMAKE_CURRENT_SOURCE_DIR, otherwise this is the directory where the compiled or generated files from the current CMakeLists.txt will go to. 如果是 in-source 编译，它跟 CMAKE_CURRENT_SOURCE_DIR 一致，如果是 out-of-source 编译，指的是目标编译目录。 |
| CMAKE_COMMAND            | CMake 可执行文件的完整路径，例如`/usr/local/bin/cmake`       |

#### 系统信息

| CMake 内置变量名称     | 含义                                           |
| ---------------------- | ---------------------------------------------- |
| CMAKE_MAJOR_VERSION    | CMAKE 主版本号， 比如 3.6.5 中的 3             |
| CMAKE_MINOR_VERSION    | CMAKE 次版本号， 比如 3.6.5 中的 6             |
| CMAKE_PATCH_VERSION    | CMAKE 补丁等级，比如 3.6.5 中的 5              |
| CMAKE_SYSTEM           | 系统名称，比如 Linux-2.6.22                    |
| CMAKE_SYSTEM_NAME      | 不包含版本的系统名，比如 Linux                 |
| CMAKE_SYSTEM_VERSION   | 系统版本，比如 2.6.22                          |
| CMAKE_SYSTEM_PROCESSOR | 处理器名称，比如 i686                          |
| UNIX                   | 所有的类 UNIX 平台为 TRUE，包括 OS X 和 cygwin |
| WIN32                  | 所有 win32 平台为 TRUE，包括 cygwin            |



## 示例

### Demo 1 - 只有单个源文件的 CMakeLists.txt 

```cmake
# 指定运行此配置文件所需的 CMake 的最低版本
cmake_minimum_required (VERSION 3.6)

# 指明项目的名称，命名为 Demo1
project (Demo1)

# 将名称为 cmath_pow.cc 的源文件编译成一个名称为 Demo 的可执行文件。
add_executable(${PROJECT_NAME} cmath_pow.cc)  # 等同于 add_executable(Demo1 cmath_pow.cc)
```



### Demo2 - 同一目录有多个源文件的 CMakeLists.txt

```cmake
# 指定运行此配置文件所需的 CMake 的最低版本
cmake_minimum_required (VERSION 3.6)

# 指明项目的名称，命名为 Demo2
project (Demo2)

# 查找当前目录下的所有源文件，
# 并将源文件的名称列表保存到变量 DIR_SRCS 
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(${PROJECT_NAME} ${DIR_SRCS})
```



### Demo3 - 多个目录中有多个源文件的 CMakeLists.txt

```
./Demo3
    |
    +--- main.cc
    |
    +--- CMakeLists.txt
    |
    +--- math/
          |
          +--- CMakeLists.txt
          |
          +--- MathFunctions.cc
          |
          +--- MathFunctions.h
```

根目录中的 CMakeLists.txt ：

```cmake
# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.6)

# 指明项目的名称，命名为 Demo3
project (Demo3)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 使用命令 add_subdirectory 指明本项目包含一个子目录 math，
# 这样 math 目录下的 CMakeLists.txt 文件和源代码也会被处理
add_subdirectory(math)

# 指定生成目标 
add_executable(${PROJECT_NAME} main.cc)

# 使用命令 target_link_libraries 指明可执行文件 Demo 需要连接一个名为 MathFunctions 的链接库
target_link_libraries(${PROJECT_NAME} MathFunctions)
```

`math`子目录中的 CMakeLists.txt

```cmake
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

# 使用命令 add_library 将目录中的源文件(${DIR_LIB_SRCS})编译为静态链接库。
add_library (MathFunctions ${DIR_LIB_SRCS})
```



### Demo4 - 自定义编译选项

CMake 允许为项目增加编译选项，从而可以根据用户的环境和需求选择最合适的编译方案。

例如，可以将 MathFunctions 库设为一个可选的库，如果该选项为 `ON` ，就使用该库定义的数学函数来进行运算。否则就调用标准库中的数学函数库。

```
./Demo4
    |
    +--- main.cc
    |
    +--- config.h.in
    |
    +--- CMakeLists.txt
    |
    +--- math/
          |
          +--- CMakeLists.txt
          |
          +--- MathFunctions.cc
          |
          +--- MathFunctions.h
```



根目录下的 CMakeLists.txt

```cmake
# CMake 最低版本要求
cmake_minimum_required(VERSION 3.6)

# 项目名称为 Demo4
project (Demo4)

# 是否使用自己的 MathFunctions 库
option(USE_MYMATH "Use provided math implementation." OFF)

# configure_file 命令用于加入一个配置头文件 config.h
# 这个文件由 CMake 从 config.h.in 生成，
# 通过这样的机制，将可以通过预定义一些参数和变量来控制代码的生成。
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
add_executable(${PROJECT_NAME} ${DIR_SRCS})

# 添加链接库
target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})
```

根目录下的 config.h.in

```
#cmakedefine USE_MYMATH
```

根目录下的  main.cc

```c++
#include <iostream>
#include "config.h"
using namespace std;

#ifdef USE_MYMATH
  #include "math/MathFunctions.h"
#else
  #include <cmath>
#endif

int main()
{
  double base;
  int component;
  cout << "Input the base and component." << endl;
  cin >> base >> component;

  double ret;
#ifdef USE_MYMATH
  cout << "Use our own Library" << endl;
  ret = power(base, component);
#else
  cout << "Use standard Library." << endl;
  ret = pow(base, component);
#endif

  cout << "pow(" << base << ", " << component << ") = " << ret << endl;
  return 0;
}
```

math子目录下的 CMakeLists.txt

```cmake
# 查找当前目录下所有的源文件
# 将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

# 指定生成链接库
add_library(MathFunctions ${DIR_LIB_SRCS})
```

math 子目录下的 MathFunctions.h

```c++
#ifndef POWER_H
#define POWER_H

extern double power(double base, int exponent);

#endif
```



math 子目录下的 MathFunctions.cc

```c++
double power(double base, int component)
{
  int ret = base;
  if(component == 0)
    return 1;

  for(int i=1; i<component; i++)
    ret = ret * base;

  return ret;
}
```



## 进阶学习

### 二进制目标

可执行文件通过 `add_executable() `指令添加，库通过`add_library()`指令添加。二进制目标之间的依赖关系可通过 `target_link_libraries()` 指令添加。

```cmake
# 定义一个静态库目标 staticObject.lib，由 a.cpp/b.cpp/c.cpp 编译得到
add_library(staticObject a.cpp b.cpp c.cpp)

# 定义一个动态库目标 dynamicObject.dll，由 a.cpp/b.cpp/c.cpp 编译得到
add_library(dynamicObject SHARED a.cpp b.cpp c.cpp)

# 生成一个可执行文件 zipapp.exe, 由 zipapp.cpp 编译得到
add_executable(zipapp zipapp.cpp)

# 将 zipapp.exe 链接静态库 archive
target_link_libraries(zipapp staticObject dynamicObject)
```



### file(GLOB) 通配符模式查找文件

An alternative to setting specific file names in the `SOURCES` variable is to use a `GLOB` command to find files using wildcard pattern matching.

```cmake
# 将 src 目录中 *.cpp 文件的文件名列表存到 SOURCES 变量中
file(GLOB SOURCES "src/*.cpp")
```



### 构建配置和构建需求

`target_include_directories()`，`target_compile_definitions()`和`target_compile_options()`指令可以用来配置构建选项和构建需要的二进制目标。



## 参考链接

* [CMake Examples](https://github.com/ttroy50/cmake-examples)

* [CMake Tutorial](https://cmake.org/cmake/help/v3.18/guide/tutorial/index.html#id8)

* [CMake Commands](https://cmake.org/cmake/help/v3.6/manual/cmake-commands.7.html)

* [CMake Useful Variables](https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/Useful-Variables)


