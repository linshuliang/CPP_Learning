# 对象移动

## 0 基础知识

### 0.1 值类型 vs 变量类型

值(value) 和 变量 (variable) 是两个独立的概念：

* 值只有类别(category) 的划分，变量只有类型(type) 的划分；
* 值不一定拥有身份(identity)，也不一定拥有变量名（例如 表达式中间结果 `i + j + k`）;



值类别 (value category) 可以分为两种：

* 左值(`lvalue, left value`) 是能被取地址、不能被移动的值；
* 右值(`rvalue, right value`) 是字面常量/表达式中间结果，可能有变量名，也可能没有；



**引用类型**是一种变量类型(variable type)。从功能上来说，引用型变量又可以看做是被引用变量的 “别名”，这两个变量只是名称不同，变量的地址是同一个（共用体中的元素也是一样）。



引用类型变量的初始化，必须遵守以下规则：

- 引用型变量在定义时必须初始化；
- 被引用的对象必须已经分配了空间，即不能为空，或空指针；
- 被引用的对象不能是地址，即指针变量、数组变量等不能被引用;
- 一旦绑定了初始值，就不能重新绑定到其他值上了;



#### 0.1.1 左值引用 v.s. 右值引用 v.s. const引用

引用类型可以分为：

* 左值引用 (`lvalue reference`) : 用 `&` 符号引用左值；
* 右值引用(`rvalue reference`) ：用 `&&` 符号引用右值；

* const引用 (`const reference`) ： 同时接受(左值/右值)进行初始化；

```c++
// const reference demo
#include <iostream>
#include <memory>
#include <utility>

class Data
{
public:
	Data(int i) : data_(i) {}
	void Print() { std::cout << "[Data::Print] " << data_ << std::endl; }
	void Display() const { std::cout << "[Data::Display] " << data_ << std::endl; }  // 常量对象只能调用 const 函数
	// 如果 const 函数不小心修改了类成员或者调用了非 const 函数，编译器会找出这个错误。

private:
	int data_;
};

void func(const Data& d)
{
	// d.Print();  // ERROR : 对象含有与成员函数不兼容的限定符，对象类型是 const Data
	d.Display();  // d 是 const 类型变量，它只能调用 const 函数
	Data a = d;
	a.Print();
}

void main()
{
	Data d1(10);
	func(d1);  // d1 是左值，const引用能接受左值初始化
	func(Data{ 15 });  // Data { 15 } 是右值， const引用能接受右值初始化
}
```



### 0.1.2 引用参数重载优先级

如果函数重载同时接受 右值引用/const 引用 参数，编译器优先重载右引用参数。

```c++
#include <iostream>
#include <memory>
#include <utility>

class Data
{
public:
	Data(int i) : data_(i) {}
	void Display() const { std::cout << "[Data::Display] " << data_ << std::endl; }  // 常量对象只能调用 const 函数

private:
	int data_;
};

void func(const Data& d)
{
	std::cout << "Call const-reference function" << std::endl;
	d.Display();
}

void func(Data&& d)
{
	std::cout << "Call right-reference function" << std::endl;
	d.Display();
}

void main()
{
	func(Data(10));
}

/* 终端输出
Call right-reference function
[Data::Display] 10
*/
```



## 1 右值引用 (rvalue reference)

所谓右值引用，就是必须绑定到右值的引用。我们可以通过 `&&` 来获得右值引用。

一般而言，左值是对象的身份，右值是对象的值。



类似任何引用，**一个右值引用也不过是某个对象的另一个名字**。为了与右值引用区分开，常规引用又称为左值引用(lvalue reference)。



**注1 ：** 左值引用不能将其绑定到（表达式求值过程中创建的临时对象）、字面常量、返回右值的表达式。

**注2 ：** 右值引用有着与左值引用完全相反的特性，我们可以将一个右值引用绑定到（表达式求值过程中创建的临时对象、字面常量、返回右值的表达式）中，但不能将一个右值引用直接绑定到一个左值中。

```c++
// Demo 1 - 左值引用/右值引用的区别
#include <iostream>
#include <utility>

void main()
{
	int i = 20;
	int& lvalue_ref_1 = i;  // 左值引用
	std::cout << lvalue_ref_1 << std::endl;
	// int& lvalie_ref_2 = 50;  // 50 是右值，无法从 int 转换为 int&

	int&& rvalue_ref_1 = 50;  // 右值引用
	std::cout << rvalue_ref_1 << std::endl;

	// int&& rvalue_ref_2 = i;  // ERROR: 无法将左值绑定到右值引用
	int&& rvalue_ref_2 = std::move(i);
	std::cout << rvalue_ref_2 << std::endl;

	// int& lvalue_ref_3 = i * 3;  // ERROR: i * 3 是一个右值，无法将右值绑定到左值引用
	int&& rvalue_ref_3 = i * 3;
	std::cout << rvalue_ref_3 << std::endl;
}
```



### 1.1 左值持久，右值短暂

* 左值有持久的状态；

* 右值要么是字面常量，要么是在表达式求值过程中创建的临时对象；



由于右值引用只能绑定到临时对象，可知：

* 所引用的对象即将被销毁
* 该对象没有其他用户



这两个特性意味着：使用右值引用的代码可以自由地接管所引用对象的资源。



### 1.2 右值引用可以解决以下场景中的移动语义缺失问题

#### 1.2.1 按值传入参数

按值传参是最符合人类思维的方式。基本的思路是：如果传入参数是为了将资源交给函数接受者，就应该按值传参。

```c++
// Demo - 按值传入参数
#include <iostream>
#include <string>

class Person
{
public:
	Person(std::string name_) : name(name_) { std::cout << "Construct " << name_ << std::endl; }

private:
	std::string name;
};

void main()
{
	Person a("Alice"); // 先调用构造函数 string(const char*)，再调用 Person(std::string) 构造函数。 
	std::string b_name = "benz";
	Person b(b_name); // 调用 Person(std::string) 构造函数
}
```



#### 1.2.2 按值返回

```c++
// Demo - 按值返回
#include <string>
#include <cstring>  // strcpy, strtok
#include <vector>
#include <iostream>

// 将输入字符串 str 以 delim 为分隔符进行分割
std::vector<std::string> str_split(const std::string& str, const std::string delim)
{
	std::vector<std::string> ret;
	if (str.empty()) return ret;

	// 将 string 转换为 char*
	char* str_chars = new char[str.length() + 1];
	strcpy(str_chars, str.c_str());
	
	char* delim_chars = new char[delim.length() + 1];
	strcpy(delim_chars, delim.c_str());

	// char* strtok(char* str, const char* delimiters);
	char* p = strtok(str_chars, delim_chars);  // 第一次调用时，参数 str 为一个C字符串，其第一个字符用作扫描令牌的起始位置
	while (p)
	{
		std::string s = p;
		ret.push_back(s);
		p = strtok(nullptr, delim_chars);  // 在随后的调用中，该函数需要一个空指针，并使用最后一个标记结束后的位置作为扫描的新起始位置
	}
	
	delete[] str_chars;
	delete[] delim_chars;
	return ret;
}

void main()
{
	std::string s = "- This, a sample string.";

	std::vector<std::string> res = str_split(s, " ,.-");
	for (int i = 0; i < res.size(); ++i)
	{
		std::cout << res[i] << std::endl;
	}
}
```

函数 `str_split` 按值返回，`return`语句又直接返回了一个栈上的左值对象时，标准要求优先调用移动构造函数，如果不符合再调用拷贝构造函数。

也就说，虽然 `ret` 是左值，仍然优先采用移动语义，从而返回类似`std::vector<std::string>` 等容器时就变得轻量。



#### 1.2.3 std::vector 的增长

当 `vector` 的 `size` 大于 `capacity` 时，在移动语义出现前，需要重新申请一块内存，并把原来的内容一个个复制过去并删除。当有了移动语义后，就只需改为移动就可以了。



#### 1.2.4 std::unique_ptr 放入容器

由于`std::vector` 等容器支持移动语义，所以将 `unique_ptr` 这种只有移动构造函数/移动赋值函数的类对象放入 `std::vector` 等容器中也就成为理所当然的事情。

 

### 1.3 误解

#### 1.3.1 被移动的值不能再使用

[C.64: A move operation should move and leave its source in a valid state](https://link.zhihu.com/?target=https%3A//isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines%23Rc-move-semantic)

很多人认为：被移动的值会进入一个**非法状态** *(invalid state)*，对应的 **内存不能再访问**。

其实，C++ 标准要求对象遵守移动语义，被移动的对象进入一个**合法但未指定状态** (valid but unspecified state)，调用该对象的方法（包括析构函数）不会出现异常，甚至在重新赋值后可以继续使用。

```c++
#include <iostream>
#include <memory>

void main()
{
	std::unique_ptr<int> p = std::make_unique<int>(1);
	std::unique_ptr<int> q = std::move(p);

	if (!p) std::cout << "p is now an nullptr" << std::endl;

	p.reset(new int{ 2 });
	std::cout << "The pointer has been reset to : " << *p << std::endl;
}
```



#### 1.3.2 Don't return std::move(local_var)

C++ 会把即将离开作用域的 **非引用类型** 的返回值当成 **右值**，对返回的对象进行移动构造。

 

#### 1.3.3 返回右值引用变量时，需使用 std::move 移动转发

无论是 **左值引用** 还是 **右值引用** 的变量（或参数）在初始化后，都是左值：

* 命名的右值引用 `(named rvalue reference)`变量是左值，但变量类型却是右值引用；
* 在作用域内，左值变量可以通过变量名被取地址，被赋值



在返回右值引用变量时，需要使用 `std::move()` 显式地移动转发，将变量"还原"为右值。

```c++
#include <iostream>
#include <memory>
#include <vector>

std::unique_ptr<int> func1(int num = 10)
{
	std::unique_ptr<int> ret = std::make_unique<int>(num);
	return ret;  // C++会把即将离开作用域的非引用类型的返回值当成右值，进而调用移动构造函数
}

std::unique_ptr<int> func2(std::unique_ptr<int>&& val)
{
	// return val;  // Error, 禁止拷贝
	return std::move(val);  // 完美转发
}

void main()
{
	auto up = func1(18);
	std::cout << "Return value of func1: " << *up << std::endl;

	auto up2 = func2(std::move(up));
	std::cout << "Return value of func2: " << *up2 << std::endl;
}
```



### 1.4 标准库 std::move 函数

```c++
template<class T>
typename remove_reference<T>::type&& move(T&& arg) noexcept;
```

* 参数

  `arg` : An object 

* 返回值

  An `rvalue reference` that refers to `arg`.



Many components of standard library implement move semantics, allowing to transfer ownership of the assets and properties of an object without having to copy them when the argument is an `rvalue`.

标准库的许多组件都实现了移动语义，从而允许直接转移对象的资产和属性的所有权，而不必在参数为右值时复制它们。



**注 ：** `std::move` 其实是 `static_cast<T&&>` 的简单封装。

```c++
// move demo cpp
#include <iostream>
#include <utility>  // move
#include <string>
#include <vector>

void main()
{
	std::string bar = "bar-string";
	std::string&& bar_rvalue_ref = std::move(bar);
	std::cout << "bar : " << bar << std::endl;  // bar-string
	std::cout << "right value reference of bar : " << bar_rvalue_ref << std::endl;  // bar-string

	std::vector<std::string> my_vec;
    // void push_back(const value_type&);
	my_vec.push_back(bar);      
    // void push_back(value_type&&);
	my_vec.push_back(bar_rvalue_ref);
	for (auto it = my_vec.begin(); it != my_vec.end(); it++) std::cout << *it << "  ";
	std::cout << std::endl;
}
```



## 2 移动语义

在 C++ 11强化了左右值概念后，提出了**移动语义** *(move semantic)* 优化：由于右值对象一般是临时对象，在移动时，对象包含的资源 **不需要先拷贝再删除**，只需要直接**从旧对象移动到新对象**。

同时，要求**被移动的对象** 处于 **合法但未指定状态**（参考1.3.1 被移动的值不能再使用]）：

- （基本要求）能正确析构（不会重复释放已经被移动了的资源，例如 `std::unique_ptr::~unique_ptr()` 检查指针是否需要 `delete`）
- （一般要求）重新赋值后，和新的对象没有差别（C++ 标准库基于这个假设）
- （更高要求）恢复为默认值（例如 `std::unique_ptr` 恢复为 `nullptr`）

由于基本类型不包含资源，其移动和拷贝相同：被移动后，保持为原有值。



### 2.1 避免先拷贝再释放资源

```c++
#include <iostream>

template<class T>
class strVec
{
public:
	strVec() : data_(nullptr), size_(0) {};  // 默认构造函数
	strVec(T* d) : data_(d), size_(0) {};
	strVec(size_t s) : data_(nullptr), size_(s) {};
	strVec(T* d, size_t s) : data_(d), size_(s) {};
	strVec(const strVec& rhs);      // copy constructor
	strVec(strVec&& rhs) noexcept;  // move constructor
	~strVec();  // 析构函数

private:
	T* data_;
	size_t size_;
};

template<class T>
strVec<T>::strVec(const strVec& rhs)
{
	std::cout << "Call Copy Constructor" << std::endl;
	data_ = new T(rhs.size_);
	strVec<T> &lhs = *this;
	lhs.size_ = rhs.size_;
	std::copy_n(rhs.data_, rhs.size_, lhs.data_);  // copy data
}

template<class T>
strVec<T>::strVec(strVec&& rhs) noexcept
{
	std::cout << "Call Move Constructor" << std::endl;
	strVec<T>& lhs = *this;
	lhs.size_ = rhs.size_;
	lhs.data_ = rhs.data_;  // move data
	rhs.size_ = 0;          // 恢复为默认情况
	rhs.data_ = nullptr;    // 恢复为默认情况
}

template<class T>
strVec<T>::~strVec()
{
	if (data_)  // 判断是否为空
	{  
		delete[] data_;
	}
}

void main()
{
	strVec<char> sv(new char[10], 10);
	strVec<char> sv2(sv);   // 拷贝构造
	strVec<char> sv3 = sv;  // 拷贝赋值
	strVec<char> sv4(std::move(sv));  // 移动构造
}
```

- 实参为左值时，拷贝构造，使用 `new[]`/`std::copy_n` 拷贝原对象的所有元素。
- 实参为右值时，移动构造，把指向原对象内存的指针 `data_`、内存大小 `size_` 拷贝到新对象，并把原对象这两个成员置 `0`



### 2.2 移动构造函数遵循的基本原则

* 如果没有定义拷贝构造/拷贝赋值/移动构造/移动赋值/析构函数的任何一个，编译器会自动生成移动构造/移动赋值函数；[Rule of Zero](https://en.cppreference.com/w/cpp/language/rule_of_three#Rule_of_zero)
* 如果需要定义拷贝构造/拷贝赋值/移动构造/移动赋值/析构函数的任何一个，不要忘了 移动构造/移动赋值 函数，否则对象会不可移动； `Rule of Five`
* 尽量使用`=default`让编译器生成默认的 拷贝构造/拷贝赋值，移动构造/移动赋值 函数，否则容易写错；[=default让编译器生成默认函数](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-eqdefault)
* 如果需要自定义 移动构造/移动赋值 函数，尽量定义为 `noexcept` 不抛出异常（编译器生成的版本会自动添加），否则 不能高效使用标准库和语言工具；



#### 2.2.1 If you can avoid defining default operations, do

原因：最简单的，通常也是最稳定最容易维护的。

```c++
#include <iostream>
#include <string>
#include <map>

struct libraryPersonInfo
{
public:
	void assignment(const std::string& name, const std::map<int, int>& req)
	{
		this->name_ = name;
		this->req_ = req;
		std::cout << "Name : " << name << std::endl;
		std::cout << "Value : ";
		for (auto it = req.begin(); it != req.end(); it++)
		{
			std::cout << it->first << " " << it->second << " ";
		}
		std::cout << std::endl;
	}

private:
	std::string name_;
	std::map<int, int> req_;
};

void main()
{
	libraryPersonInfo person;
	std::string name = "lin";
	std::map<int, int> req;
	req[5] = 1;
	person.assignment(name, req);
}
```

成员变量 `name_` 和 `req_`  都是标准库类型，即使不定义`拷贝构造/拷贝赋值/移动构造/移动赋值/析构函数`的任何一个，这个类生成的默认函数就已经是最好的。



#### 2.2.2 If you define or `=delete` any copy, move, or destruction function, define or `=delete` them all

拷贝构造/拷贝赋值，移动构造/移动赋值，析构函数，这三者是紧密联系的，如果声明或者删除(`=delete`)了其中一个，那么也要声明或者删除其余的。



* 如果声明了 拷贝构造/拷贝赋值，移动构造/移动赋值，析构函数中的任何一个，即使是`=delete`或者`=default`，那么编译器就会取消对移动构造/移动赋值函数的隐式声明，此时对象没有移动语义。
* 如果声明了 移动构造/移动赋值函数，即使是`=delete`或者`=default`，那么编译器就会取消对 拷贝构造/拷贝赋值函数的隐式声明，此时对象没有拷贝语义。



一旦声明了拷贝构造/拷贝赋值，移动构造/移动赋值，析构函数中的任何一个，就要声明所有其他的，以免避免产生不必要的影响，例如将所有潜在的动作转换为更昂贵的副本，或者仅进行类移动。



**注** ： 如果你想使用默认实现，用`=default`来表示你有意为此功能执行此操作。如果你不希望生成默认的构造函数/析构函数，那么用`=delete` 来禁止。

**注**：拷贝构造/拷贝赋值，移动构造/移动赋值，析构函数的形式：

```c++
class X
{
public:
    virtual ~X();  // destructor
    X(const X&);   // copy constructor
    X& operator=(const X&);  // copy assignment
    X(X&&);        // move constructor
    X& operator=(const X&&);  // move assignment
}
```



如果声明了拷贝构造函数，但没有声明移动构造/移动赋值函数，那么这个类将缺失移动语义，即使参数是右值，执行的也是拷贝：

```c++
#include <iostream>
#include <memory>

class Foo
{
public:
	Foo() = default;
	Foo(const Foo&) { std::cout << "Copy Constructor" << std::endl; };  // copy constructor
};

void main()
{
	Foo x;
	Foo y(x);
	Foo z(std::move(x));
}

/*  程序输出
Copy Constructor
Copy Constructor
*/
```

**拷贝构造函数**满足对应的**移动构造函数**的要求：它会拷贝给定对象，并将原对象置于有效状态。



如果声明了移动构造函数，但没有声明拷贝构造/拷贝赋值函数，那么这个类将缺失拷贝语义。无法用一个左值完成构造。

```c++
#include <iostream>
#include <memory>

class Foo
{
public:
	Foo() = default;
	Foo(Foo&&) { std::cout << "Move Constructor" << std::endl; };  // move constructor
};

void main()
{
	Foo x;
	// Foo y(x);  // Foo(const Foo&) = delete; 无法引用已经删除的函数
	Foo z(std::move(x));
}

/*  程序输出
Move Constructor
*/
```



#### 2.2.3 Use `=default` if you have to be explicit about using the default semantics

**Reason** : The compiler is more likely to get the default semantics right and you can't implement these functions better than the compiler.

编译器能够自动生成的默认函数，通常具有正确的拷贝/移动语义。如果拷贝/移动语义没有特殊的自定义要求，请使用`=default`。



```c++
#include <iostream>
#include <string>

// 因为写了析构函数，因此必须显式声明 拷贝构造/拷贝赋值，移动构造/移动赋值，=default 表示让编译器自动生成默认的
class Tracer 
{
private:
    std::string message;

public:
    Tracer(const std::string& m) : message{ m } { std::cerr << "entering " << message << '\n'; }
    ~Tracer() { std::cerr << "exiting " << message << '\n'; }

    Tracer(const Tracer&) = default;
    Tracer& operator=(const Tracer&) = default;
    Tracer(Tracer&&) = default;
    Tracer& operator=(Tracer&&) = default;
};

// 写出复制和移动操作的主体是冗长，乏味且容易出错的, 编译器会做得更好。
class BadTracer 
{
private:
    std::string message;
public:
    BadTracer(const std::string& m) : message{ m } { std::cerr << "entering " << message << '\n'; }
    ~BadTracer() { std::cerr << "exiting " << message << '\n'; }

    BadTracer(const BadTracer& a) : message{ a.message } {}
    BadTracer& operator=(const BadTracer& a) { message = a.message; return *this; }
    BadTracer(BadTracer&& a) : message(a.message) {}
    BadTracer& operator=(BadTracer&& a) { message = a.message; return *this; }
};

void main()
{
    Tracer gt("good tracer");
    BadTracer bt("bad tracer");
}
```



#### 2.2.4 不抛出异常的移动构造函数和移动赋值运算符必须标记为 noexcept

`noexcept` 是我们承诺一个函数不抛出异常的一种方法。



例如：`std::vector` 使用 `std::move_if_noexcept()` 进行元素的转移操作：

- 优先 使用 `noexcept` 移动构造函数（高效；不抛出异常）
- 其次 使用 拷贝构造函数（低效；如果异常，可以回滚）
- 再次 使用 非 `noexcept` 移动构造函数（高效；如果异常，**无法回滚**）
- 最后 如果 不可拷贝、不可移动，**编译失败**



如果没有定义移动构造函数或自定义的移动构造函数没有 `noexcept`，会导致 `std::vector` 扩容时执行无用的拷贝，**不易发现**。







## 参考

[如何评价 C++11 的右值引用（Rvalue reference）特性？](https://www.zhihu.com/question/22111546)

[深入浅出 C++ 11 右值引用](https://zhuanlan.zhihu.com/p/107445960)


