# 对象移动

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

函数 `str_split` 按值返回，`return` 语句又直接返回了一个栈上的左值对象时，标准要求优先调用移动构造函数，如果不符合再调用拷贝构造函数。

也就说，虽然 `ret` 是左值，仍然优先采用移动语义，从而返回类似`std::vector<std::string>` 等容器时就变得轻量。



#### 1.2.3 std::vector 的增长

当 `vector` 的 `size` 大于 `capacity` 时，在移动语义出现前，需要重新申请一块内存，并把原来的内容一个个复制过去并删除。当有了移动语义后，就只需改为移动就可以了。



#### 1.2.4 std::unique_ptr 放入容器

由于`std::vector` 等容器支持移动语义，所以将 `unique_ptr` 这种只有移动拷贝函数/移动赋值函数的类对象放入 `std::vector` 等容器中也就称为理所当然的事情。

 

### 1.3 误解

#### 1.3.1 被移动的值不能再使用

[C.64: A move operation should move and leave its source in a valid state](https://link.zhihu.com/?target=https%3A//isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines%23Rc-move-semantic)

很多人认为：被移动的值会进入一个**非法状态** *(invalid state)*，对应的 **内存不能再访问**。

其实，C++ 标准要求对象遵守移动语义，被移动的对象进入一个**合法但未指定状态** *(valid but unspecified state)*，调用该对象的方法（包括析构函数）不会出现异常，甚至在重新赋值后可以继续使用。

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

C++ 会把 即将离开作用域的 **非引用类型** 的返回值当成 **右值**，对返回的对象进行移动构造。

 





### 标准库 std::move 函数

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









## 参考

[如何评价 C++11 的右值引用（Rvalue reference）特性？](https://www.zhihu.com/question/22111546)

[深入浅出 C++ 11 右值引用](https://zhuanlan.zhihu.com/p/107445960)


