# C++ static 关键字

C++ 中的`static` 关键字用于控制变量的存储方式和可见性。



`static` 关键字的作用：

* `static` 作用于局部变量：使得局部变量保存在静态存储区，保持变量内容的持久化。
* `static` 作用于全局变量：非`static`全局变量对整个工程可见，`static`全局变量仅对当前文件可见。
* 静态存储区中，所有字节默认都是 `0x00`。在初始化稀疏矩阵时，可省略将数据全置为0的操作，只需把不为0的几个元素赋值。
* `static` 作用于类内成员，由该类的所有对象共同维护和使用，从而实现同一个类的不同对象数据共享。



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



## 4 作用于类的数据成员

在类内数据成员的声明前加`static` 关键字，该数据成员就是类内的静态数据成员。其特点如下：

* 静态数据成员存储于静态存储区。静态数据成员在定义时分配存储空间，不能在类声明中定义。
* 类的静态数据成员，在声明时加关键字 `static`，而且不能在声明时初始化（带有类内初始值设定项的成员必须为常量）。必须在类外初始化（在类外初始化时不能带 `static` 关键字）。原因：在定义类时，已在静态存储区分配了内存，初始化不负责静态存储区的分配，故不能加关键字 `static`。
* 和普通数据成员一样，静态数据成员也遵从 `protected, private, public` 访问规则。



```c++
#include <iostream>

class Point 
{
public:	
	Point(int x = 0, int y = 0) : x_(x), y_(y) 
	{
		count++;
	}

	Point(const Point &p) 
	{
		x_ = p.x_;
		y_ = p.y_;
		count++;
	}
	
	~Point() { count--; }
	
	int getX() { return x_; }
	int getY() { return y_; }

	static void showCount() 
	{
		std::cout << "Object Count = " << count << std::endl;
	}

private:	
	int x_, y_;
	static int count;
};

int Point::count = 0;  // 在定义 class Point 时，已在静态存储区分配了内存，初始化时不负责静态存储区的分配，故不能加关键字 static

void main()
{
	Point p1(10, 20);
	Point::showCount();

	Point p2(5, 6);
	Point::showCount();

	system("pause");
}
```



## 5 作用于类的成员函数

* 类的静态成员函数属于整个类，而非类的对象。所以类的静态成员函数也没有`this`指针，这就导致了它仅能访问类的静态数据和静态成员函数。
* 类的静态成员函数不能声明为 `virtual`。因为 `virtual` 虚函数是动态联编，在创建对象时生成虚函数表`vtable` 和虚表指针 `vptr`，然后调用时再由`vptr`访问 `vtable`。而静态成员函数是在定义类时就已经完成编译，在静态存储区中分配了内存空间来存储函数指针，根本就不存在生成虚函数表和虚表指针等操作。











