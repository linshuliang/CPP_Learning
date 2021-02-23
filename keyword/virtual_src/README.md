# virtual 关键字

## 1 面向对象程序设计

面向对象程序设计（object-oriented programming）的核心思想是：数据抽象，继承，动态绑定。

* 通过数据抽象，我们可以将类的接口和实现分离；
* 通过继承，可以定义相似的类型，并对其相似关系建模；
* 通过动态绑定，可以在一定程度上忽略相似类型的区别，而使用统一的方式来使用它们的对象。



### 1.1 数据抽象

 类的基本思想是：

* 数据抽象 (data abstraction)
* 封装 (encapsulation)



数据抽象是一种依赖于接口(interface) 和实现 (implementation) 相分离的编程技术：

* 类的接口包括用户所能执行的操作；

* 类的实现包括类的数据成员，负责接口实现的函数体以及类所需的各种私有函数。



```c++
// Demo ： 数据抽象和封装
// 将用户所需的接口暴露提供，将具体实现封装隐藏
#ifndef __DEMO_MODULE_H__
#define __DEMO_MODULE_H__

#include <memory>
#include <string>

class Module
{
public:
    Module();
        
    int Init(const bool USE_GPU, const int device_id);
    int Run(const std::string& req, bool& rsp);

private:
    class Impl;
    std::shared_ptr<Impl> impl_;
};

#endif
```



```c++
// Demo ： 类的实现
#include "Module.h"     // 头文件
#include "ClsModule.h"  // 头文件
#include "SegModule.h"  // 头文件

class Module::Impl
{
public:
	Init(const bool USE_GPU, const int device_id);
    Run(const std::string& req, bool& rsp)
        
private:
    ClsModule eve_cls;
    SegModule eve_seg;
};

//______________________________________________________________________________
//_____________________________Interface________________________________________
Module::Module() :impl_(std::make_shared<Impl>()) {};

int Module::Init(const bool USE_GPU, const int device_id)
{
	return impl_->Init(USE_GPU, device_id);
}

int Module::Run(const std::string& req, bool& rsp)
{
	return impl_->Run(req, rsp);
}
```



## 2 继承与多态

### 2.1 基类与派生类对象的关系

基类对象与派生类对象之间存在向上赋值(up-casting)相容性。包括以下几种情况： 

* 把派生类对象赋值给基类对象；

* 把派生类对象的地址赋值给基类指针； 

* 用派生类对象初始化基类对象的引用。



 向下赋值(down-casting) 是不可行的：

* 不能把基类对象赋值给派生类对象；
* 不能把基类对象的地址赋值给派生类对象的指针；
* 不能把基类对象作为派生对象的引用。



```c++
// Demo - upcasting
#include <iostream>

class A 
{
private:
	int a;
public:
	void setA(int x) { a = x; }
	int getA() { return a; }
};

class B : public A 
{
private:
	int b;
public:
	void setB(int x) { b = x; }
	int getB() { return b; }
};

void main() 
{
	A a1;
	B b1;
	a1.setA(1);
	b1.setA(2);
	std::cout << "a1 = " << a1.getA() << std::endl;  // 1
	std::cout << "b1 = " << b1.getA() << std::endl;  // 2

	// 把派生类对象赋值给基类对象
	a1 = b1;  // A& A::operator=(const A&);
	std::cout << "a1 = " << a1.getA() << std::endl;  // 2
	std::cout << "b1 = " << b1.getA() << std::endl;  // 2
	
	a1.setA(10);
	std::cout << "a1 = " << a1.getA() << std::endl;  // 10
	std::cout << "b1 = " << b1.getA() << std::endl;  // 2

	// 把派生类对象的地址赋值给基类指针
	A* ap = &b1;
	std::cout << "*ap = " << ap->getA() << std::endl; // 2

	// 用派生类对象初始化基类对象的引用
	A& ac = b1;
	std::cout << "ac = " << ac.getA() << std::endl;   // 2

    // b1 = a1;      // ERROR : 无法把基类对象赋值给派生类对象
	// B* bp = &a1;  // ERROR : 无法将基类对象的地址赋值给派生类指针
	// B& bc = a1;   // ERROR : 无法用派生类对象初始化基类对象的引用
    
	system("pause");
}
```





## 3 虚函数表剖析

为了实现 C++ 的多态，C++ 使用了一种动态绑定的技术，这个技术的核心是虚函数表 (vtable)。

### 3.1 虚函数表

每个包含虚函数的类，都包含一个虚函数表。

```C++
// Demo - 虚函数表
#include <iostream>

class A 
{
public:
	virtual void vfunc1() 
	{ 
		std::cout << "A.size() : " << sizeof(*this) << std::endl; 
		// 16, 其中两个整数为8个字节，64位程序的vptr为64位，也即8个字节
	}  
	
	virtual void vfunc2() 
	{ 
		std::cout << "sizeof(int) : " << sizeof(this->m_data1) << std::endl;  // 4
	}
	
    void func1();
    void func2();

private:
	int m_data1;
	int m_data2;
};

class B : public A
{
public:
	void vfunc1() 
	{ 
		std::cout << "B.size() : " << sizeof(*this) << std::endl;
		// 16, 其中子类的两个整数为8个字节，64位程序的vptr为64位，也即8个字节
	}

	void vfunc2()
	{
		std::cout << "sizeof(void*) : " << sizeof(void*) << std::endl;  // 8
	}

	void func1();
	void func2();
};

void main()
{
	A a_instance;
	a_instance.vfunc1();
	a_instance.vfunc2();

	B b_instance;
	b_instance.vfunc1();
	b_instance.vfunc2();
	system("pause");
}
```

![](.\vtable_1.png)

虚函数表是一个函数指针数组，其元素是虚函数的指针。需要指出的是，普通函数是非虚函数，其调用不需要经过虚函数表，所以虚函数表的元素并不包括普通函数的函数指针。



**注意**：虚函数表是在编译阶段设置的静态数组，虚函数表包含可由类的对象调用的虚函数的条目。



### 3.2 虚表指针

虚函数表属于类，而不是某个具体的对象，一个类只需要一个虚函数表，同一个类的所有对象都使用同一个虚函数表。

编译器在类中添加了一个指针(`void*`) ，称之为虚表指针(`vptr, virtual pointer`)，用来指向虚函数表。这样，在类对象创建时就拥有这个虚表指针(`vptr`)，且这个指针的值会自动指向类的虚函数表。

![](.\vptr.png)



### 3.3 动态绑定

```c++
// Demo - 动态绑定
#include <iostream>

class A
{
public:
	virtual void vfunc1()
	{
		std::cout << "A.size() : " << sizeof(*this) << std::endl;
		// 16, 其中两个整数为8个字节，64位程序的vptr为64位，也即8个字节
	}

	virtual void vfunc2()
	{
		std::cout << "sizeof(int) : " << sizeof(this->m_data1) << std::endl;  // 4
	}

	void func1();
	void func2();

private:
	int m_data1;
	int m_data2;
};

class B : public A
{
public:
	void vfunc1()
	{
		std::cout << "B.size() : " << sizeof(*this) << std::endl;
		// 24, 其中三个整数为12个字节，64位程序的vptr为64位，也即8个字节
	}

	void vfunc2()
	{
		std::cout << "sizeof(void*) : " << sizeof(void*) << std::endl;  // 8
	}

	void func1();
	void func2();

private:
	int m_data3;
};

class C : public B 
{
public:
	virtual void vfunc2()
	{
		std::cout << "C.size() : " << sizeof(*this) << std::endl;
		// 32, 其中五个整数为20个字节，64位程序的vptr为64位，也即8个字节
	}
	void func2();

private:
	int m_data1, m_data4;
};

void main()
{
	A a_instance;
	a_instance.vfunc1();

	B b_instance;
	b_instance.vfunc1();

	C c_instance;
	c_instance.vfunc2();

	system("pause");
}
```

![](.\dynamic_binding.png)



记住以下要诀：

* 每个类都有相应的虚函数表，同一个类的所有对象有相同的虚函数表;
* 类的每个对象都有各自的虚表指针，指向所属类的虚函数表;
* 虚函数表的指针会指向其继承的最近的一个类的虚函数。



我们将经过虚函数表调用虚函数的过程称为动态绑定，其表现出来的现象称为运行时多态。



#### 3.3.1 什么时候会执行函数的动态绑定？

* 通过指针（或引用）来调用函数；
* 指针 `upcast` 向上转型（继承类向基类的转换称为 `upcast`）；
* 调用的是虚函数。



如果一个函数的调用符合以上三个条件，编译器会将函数调用编译成动态绑定，其函数的调用过程走的是上述通过虚函数表的机制。



## 4 虚函数使用要诀

### 4.1 构造函数不能为虚函数

* 从存储空间角度，编译期会生成静态的虚函数表，在创建类对象时会将对象的 vptr 指向 vtable。 如果构造函数是虚的，vptr 还没有实例化，怎么找vtable呢？

* 从使用角度，虚函数主要用于动态联编，使得基类指针或引用在调用函数时可根据实际指向的对象来调用。构造函数是在创建对象时自动调用的，不可能通过父类的指针或者引用去调用，因此也就规定构造函数不能是虚函数。



### 4.2 当存在动态联编时，将基类的析构函数设为虚函数

当不存在继承关系，或者不需要使用基类指针（或引用）去操作派生类对象时，不必将析构函数声明为虚函数。

将析构函数声明为虚函数，则在编译期会为这个类生成一个静态的虚函数表(vtable)，并定义一个虚函数指针（`void* vptr`）。



#### 4.2.1 为何要将析构函数声明为虚函数？

将析构函数声明为虚函数，可以防止内存泄漏。



派生类对象的构造：

* 调用基类的构造函数
* 调用派生类的构造函数



派生类对象析构：

* 调用派生类的析构函数
* 调用基类的析构函数



总之： 先构造的后释放。



```c++
#include <iostream>

class Base
{
public:
	Base()
	{
		std::cout << "Construct Base" << std::endl;
	}

	virtual ~Base()
	{
		std::cout << "Destruct Base" << std::endl;
	}

private:
	int i;
};

class Inherit : public Base
{
public:
	Inherit()
	{
		std::cout << "Construct Inherit" << std::endl;
	}

	~Inherit()
	{
		std::cout << "Destruct Inherit" << std::endl;
	}

private:
	int num;
};

void main()
{
	Base *bi = new Inherit();
	delete bi;

	Base *b = new Base();
	delete b;

	system("pause");
}
```

程序输出为：

```shell
/*
Construct Base
Construct Inherit
Destruct Inherit
Destruct Base
Construct Base
Destruct Base
*/
```



在继承中，动态联编已经发生了，此时如果不将析构函数声明为虚函数，则有可能会出现内存泄漏等情况。











