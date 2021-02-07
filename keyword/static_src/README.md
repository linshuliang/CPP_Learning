# C++ static 关键字

C++ 中的`static` 关键字用于控制变量的存储方式和可见性。



`static` 关键字的作用：

* `static` 作用于局部变量：使得局部变量保存在静态存储区，保持变量内容的持久化。
* `static` 作用于全局变量：非`static`全局变量对整个工程可见，`static`全局变量仅对当前文件可见。
* 静态存储区中，所有字节默认都是 `0x00`。在初始化稀疏矩阵时，可省略将数据全置为0的操作，只需把不为0的几个元素赋值。
* `static` 作用于函数 ： `static` 函数只能在声明它的文件中调用，其他文件不能调用函数。



## 1 作用于局部变量

把局部变量声明为 `static`，它的生存期为整个源程序，但它的作用域与其他局部变量相同。

```c++
#include <iostream>

void test()
{
	static int num = 0;
	num++;
	std::cout << num << std::endl;
}

void main()
{
	for (int i = 0; i < 10; i++) test();
	system("pause");
}

// 输出： 1 2 3 4 5 6 7 8 9 10
// 如果不加 static，那么输出变为: 1 1 1 1 1 1 1 1 1 1
```



**局部变量**：

* 不加 `static` 修饰，局部变量在栈中分配内存，当离开作用域时，对象就会被销毁，栈内存就会被释放。
* 加 `static` 修饰，`static`变量在第一次初始化时在静态存储区分配内存，即使离开作用域，变量也不会被销毁，直到程序结束 static 变量才会被销毁，静态存储区的资源被释放。



**全局变量和 `static` 局部变量的区别**:

* static 变量和全局变量都存储在静态存储区。与全局变量相比，`static`局部变量可以控制变量的可见范围，只能在定义该`static`变量的函数中使用该变量。
* 如果想将函数中变量的值保存至下一次调用，也可使用全局变量，但全局变量有极大的缺点：破坏了变量的访问范围。使得此变量不仅仅可在此函数中被修改。



## 2 作用于全局变量

在定义不需要与其他文件共享的全局变量时，加`static`关键字能有效降低程序模块之间的耦合，避免不同文件同名变量的冲突，且不会被误用。

如果在一个文件中定义了全局变量，在另一个文件中需要用到此变量，则需要用 `extern` 关键字作声明。

```c++
// file1.cpp
static char a = 'A';
char b = 'B';
```

```c++
// file2.cpp
#include <iostream>

void main()
{
	// extern char a;  // 编译时就会报错 : 无法解析的变量
	// std::cout << a << std::endl;  

	extern char b;
	std::cout << b << std::endl;
	system("pause");
}
```

编译生成可执行文件：

```cmake
add_executable(static_global_var_demo "file1.cpp" "file2.cpp")
```

小结：

* 非`static` 全局变量，在整个工程中可见。使用工程中其他源文件定义的全局变量时，只需加关键字`extern` 声明即可。
* `static`全局变量，仅在定义的源文件中可用。



## 3 静态存储区的所有字节默认为 `0x00`

```c++
#include <iostream>

int a;

void main()
{
	static char b[10];
	std::cout << a << std::endl;  // 0
	std::cout << b << std::endl;  // 空字符串
	system("pause");
}
```



## 4 static 静态函数

函数的使用方式与全局变量类似，在函数返回类型前加`static` 关键字，就是静态函数。其特性如下：

* 静态函数只能在声明它的文件中可见，其他文件不能引用这个函数；
* 不同的文件，可以声明和定义同名的静态函数，互不影响；
* 非静态函数，可以在另一个文件中直接调用，甚至不必使用 `extern` 声明；

```c++
// Demo : static function 
#include <iostream>
#include <cstdlib>

static int getInt()
{
	return rand() % 100;
}

void main()
{
	for (int i = 0; i < 10; i++) std::cout << getInt() << std::endl;
	system("pause");
}
```


