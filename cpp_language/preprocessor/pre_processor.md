# C++ 预处理器

预处理器是一些指令，指示编译器在实际编译之前所需完成的预处理。

所有的预处理器指令都是以井号 `#` 开头，只有空格字符可以出现在预处理指令之前。预处理指令不是 C++ 语句，所以它们不会以分号（;）结尾。

 `#include` 指令 ： 这个宏用于把头文件包含到源文件中。

C++ 还支持很多预处理指令，比如： `#include`, `#define`, `#if`, `#else`, `#line`, `#ifdef`, `#ifndef`, `#endif`



## #define 预处理

\#define 预处理指令用于创建符号常量。该符号常量通常称为**宏**，指令的一般形式是：

```c++
#define macro-name replacement-text
```

当这一行代码出现在一个文件中时，在该文件中后续出现的所有宏都将会在程序编译之前被替换为 **replacement-text**，例如：

```c++
#include <iostream>
using namespace std;
 
#define PI 3.14159
 
int main()
{
    cout << "Value of PI :" << PI << endl; 
    return 0;
}
```



### 参数宏

可以使用 `#define` 来定义一个带有参数的宏。

```c++
#include <iostream>
using namespace std;
 
#define MIN(a,b) (a<b ? a : b)
 
int main ()
{
   int i, j;
   i = 100;
   j = 30;
   cout <<"较小的值为：" << MIN(i, j) << endl;
    return 0;
}
```



### 条件编译

有几个指令可以用来有选择地对部分程序源代码进行编译，这个过程被称为条件编译。



**例1 ： 定义一个变量**

```c++
#ifndef NULL
#define NULL 0
#endif
```



**例2 ：在调试时进行编译 **

在调试时进行编译，调试开关可以使用一个宏来实现，如下：

```c++
#ifdef DEBUG
	std::cout << "Debug Mode " << std::endl;
#endif
```

如果在指令 `#ifdef DEBUG` 之前已经定义了符号常量 `DEBUG`， 则会对程序中的  `std::cout` 语句进行编译。



**例3 ： 使用 #if 0  注释**

可以使用 `#if 0` 语句注释程序的一部分。如下：

```c++
#if 0
	不进行编译的代码
#endif
```
