# C++ 内存空间

**C++ 的内存空间分为三种**：

* 静态内存
* 栈内存
* 自由空间`(free storage)` 或堆`(heap)`



**内存空间与变量类型的对应关系**：

* 静态内存用来保存局部`static`对象，类`static`数据成员，以及定义在任何函数之外的变量；
* 栈内存用来保存定义在函数内的非`static`对象；
* 程序用堆来存储动态分配（`dynamically allocate`) 的对象；



**变量的创建与销毁**：

* 静态内存中的对象由编译器自动创建和销毁，`static`对象在使用之前分配，在程序结束时销毁；
* 栈内存中的对象由编译器自动创建和销毁，栈对象仅在其定义的程序块运行时才存在；
* 动态对象的生存期由程序来控制，当动态对象不再使用时，必须显式销毁它们。



**动态内存与智能指针**:

在C++中，动态内存的管理是通过一对运算符来完成的：

* `new`        ：在动态内存中为对象分配空间，并返回一个指向该对象的指针；
* `delete`  ：接受一个动态对象的指针，销毁该对象，并释放与之关联的内存；



c++11 引入了智能指针。智能指针的行为类似常规指针，重要的区别是它负责自动释放所指向的对象。新标准库提供的智能指针的区别在于管理底层指针的方式：

* `shared_ptr` : 允许多个指针指向同一个对象；
* `unique_ptr` : 独占所指向的对象；
* `weak_ptr`     : 一种弱引用，指向`shared_ptr`所管理的对象。



程序使用动态内存出于以下三种原因之一：

* 程序不知道自己需要使用多少对象；
* 程序不知道所需对象的准确类型；
* 程序需要在多个对象间共享数据；



### 智能指针与异常

如果使用智能指针，即使程序块过早结束，智能指针也能确保在内存不需要时将其释放。

```c++
void f()
{
  std::shared_ptr<int> sp(new int (10));
   // 这段代码抛出一个异常，且在 f 中未捕获
}  // 函数结束后， shared_ptr 自动释放内存
```



如果是用`new`分配的内存，如果在`delete`之前发生异常，则内存不会被释放。

```c++
void g()
{
  int *p = new int (32);
  // 这段代码抛出一个异常，且在 f 中未捕获
  delete p;
} // 在 new 和 delete 之间发生了异常，且异常未被捕获，那么内存永远都不会被释放。
```



## std::shared_ptr

c++ 中动态内存的管理是通过`new`和`delete`来完成的，只要保证`new`和`delete`的配对使用，是没有问题的。但是有时候我们会忘记释放内存，甚至有时候我们根本就不知道什么时候释放内存。特别是在多个线程间共享数据时，更难判断内存该何时释放。这种情况下机器就容易产生引用非法内存的指针。

`std::shared_ptr` 用于管理指针的存储，提供有限的`垃圾收集(garbage collection)`的功能，并可能与其他对象共享管理权。



### std::make_shared

``` c++
template<typename T>
shared_ptr<T> make_shared(Args&& ... args);
```

用于创建一个`shared_ptr`智能指针，这是推荐的安全的初始化方式。

类似于`vector`的成员函数`emplace`，`make_shared`的参数`args`用作类`T`的构造函数的参数，从而创建出一个类`T`对象，并使得智能指针`shared_ptr<T>`指向此对象。

```c++
/*Demo 1: std::make_shared */
#include <iostream>
#include <memory>
#include <string>

int main()
{
  // 指向 int 的智能指针
  std::shared_ptr<int> foo = std::make_shared<int> (10);
  
  // 指向 std::string 的智能指针
  std::shared_ptr<std::string> bar = std::make_shared<std::string>(6, '2');
  
  // 指向 std::pair<int, int> 的智能指针
  std::shared_ptr<std::pair<int, int>> baz = std::make_shared<std::pair<int, int>> (30, 50);
  
  std::cout << "*foo: " << *foo << std::endl;
  std::cout << "*bar: " << *bar << std::endl;
  std::cout << "*baz: " << baz->first << "  " << baz->second << std::endl;
  
  return 0;
}
```



## shared_ptr 的引用计数

每个`shared_ptr`都有与指向对象关联的计数器，通常称其为`引用计数(reference count)`。

下面的操作，会使得计数器递增：

* 拷贝构造
* 拷贝赋值
* 将`shared_ptr`对象作为参数传递给一个函数
* 将`shared_ptr`对象作为函数的返回值

下面的操作，会使得计数器递减：

* `shared_ptr` 对象被销毁
* `shared_ptr` 对象被赋予新值

```c++
std::shared_ptr<int> r = std::make_shared<int>(50);
r = q;  // 给 r 赋值
				// 递增 q 指向的对象的引用计数
				// 递减 r 原来指向对象的引用计数
				// 如果 r 原来指向对象的引用计数为0，则自动释放该对象
```

**注意：** 只有用一个`shared_ptr`为另一个`shared_ptr`赋值时，才将这两个指针关联起来，直接使用地址值会导致各个`shared_ptr`独立。



## shared_ptr 的析构函数

`shared_ptr`的析构函数会递减它所指向的对象的引用计数。如果引用计数变为`0`，那么`shared_ptr`的析构函数就会销毁对象，并释放它占用的内存。



### std::shared_ptr 类的构造函数

```c++
// default constructor
// owns no pointer, use_count == 0
constexpr shared_ptr() noexcept;

// construct from pointer
// The object owns p, setting the use_count to 1
// 禁止隐式的类型转换
template<typename U>
explicit shared_ptr(U* p);

// construct from `pointer + deleter`
// The object owns p, setting the use_count to 1
template<typename U, typename D>
explicit shared_ptr(U* p, D del);

// construct from `pointer + deleter + allocator`
template<typename U, typename D, typename Alloc>
shared_ptr(U* p, D del, Alloc alloc);

// copy constructor
template<typename U>
shared_ptr(const shared_ptr<U>& x) noexcept;
// If x is not empty, the object shares ownership of x's assets and increases the use_count by 1.
// If x is empty, an empty object is constructed (the same as default constructed).

// move constructor
// The object acquires the content managed by x including its owned pointer, x becomes an empty object.
template<typename U>
shared_ptr(shared_ptr<U>&& x) noexcept;

// copy from weak_ptr
template<typename U>
explicit shared_ptr(const weak_ptr<U>& x);
// If x is not empty, the object shares ownership of x's assets and increases the use_count by 1.
// If x is empty, an empty object is constructed (the same as default constructer).

// move from unique_ptr
// The object acquires the content managed by x including its owned pointer, x becomes an empty object.
template<typename U, typename D>
shared_ptr(unique_ptr<U, D>&& x);
```



### std::shared_ptr 的成员函数

| 成员函数名        | 作用                                                         |
| ----------------- | ------------------------------------------------------------ |
| `~shared_ptr();`  | 析构函数                                                     |
| `operator=()`     | 赋值                                                         |
| `operator*()`     | 解引用对象                                                   |
| `operator->()`    | 解引用对象的成员，Returns a pointer to the object pointed by the *stored pointer* in order to access one of its members. |
| `operator bool()` | Returns whether the stored pointer is a null pointer. The stored pointer points to the object the shared_ptr object dereferences to, which is generally the same as its *owned pointer*. |
| `get()`           | 返回指针。Returns the *stored pointer*.                      |
| `reset()`         | 重置指针。Reset pointer.                                     |
| `swap()`          | 交换。Exchanges the contents of the `shared_ptr` object with those of *x*, transferring ownership of any managed object between them without destroying or altering the `use_count` of either. |
| `use_count()`     | 引用计数。Returns the number of `shared_ptr` objects that share ownership over the same pointer. |
| `unique()`        | 引用计数是否为1。Returns whether the `shared_ptr` object does not share ownership over its pointer with other `shared_ptr` objects (i.e., it is *unique*). |



### std::shared_ptr::operator=

#### 拷贝赋值函数

```c++
template<class U>
shared_ptr& operator=(const shared_ptr<U>& x) noexcept;
```

#### 移动赋值函数

```c++
template<class U>
shared_ptr& operator=(shared_ptr<U>&& x) noexcept;
```

**Demo2  std::shared_ptr::operator=**

```c++
#include <iostream>
#include <memory>

int main()
{
	std::shared_ptr<int> foo;
	std::shared_ptr<int> bar = std::make_shared<int>(10);

	// template<typename U>
	// shared_ptr& operator=(const shared_ptr<U>& x) noexcept;
	foo = bar;

	// template<typename U>
	// shared_ptr& operator=(shared_ptr<U>&& x) noexcept;
	bar = std::move(std::make_shared<int>(20));
	
	std::cout << "*foo: " << *foo << std::endl;
	std::cout << "*bar: " << *bar << std::endl;

	return 0;
}
```



### 解引用

#### 解引用指针对象

```c++
element_type& operator*() const noexcept;
```

**Demo3 std::shared_ptr::operator* **

```c++
#include <iostream>
#include <memory>

int main()
{
	std::shared_ptr<int> foo(new int);
	std::shared_ptr<int> bar(new int (10));

	*foo = *bar * 2;

	std::cout << "*foo: " << *foo << std::endl;
	std::cout << "*bar: " << *bar << std::endl;

	return 0;
}
```



#### 解引用指针对象的成员变量

```c++
element_type& operator->() const noexcept;
```

**Demo4 std::shared_ptr::operator->**

```c++
#include <iostream>
#include <memory>

struct cla
{
	int a;
	int b;
};

int main()
{
	std::shared_ptr<cla> foo;
	std::shared_ptr<cla> bar (new cla);

	// template<typename U>
	// shared_ptr& operator=(const shared_ptr<U>& );
	foo = bar;

	foo->a = 10;
	bar->b = 20;

	if(foo) std::cout << "foo: " << foo->a << " " << foo->b << std::endl;
	if(bar) std::cout << "bar: " << bar->a << " " << bar->b << std::endl;

	return 0;
}
```



### 返回内置指针

智能指针定义了一个名为`get()`的函数，它返回一个内置指针，指向智能指针管理的对象。`get()`函数的设计原则是：我们向不能使用智能指针的代码传递一个内置指针，例如：



**Demo5-1 std::shared_ptr::get**

```c++
#include <iostream>
#include <memory>
using namespace std;

void useShared_ptr(int *p)
{
    cout<< *p <<endl;
}

int main()
{
    shared_ptr<int> p1 = make_shared<int>(32);
    useShared_ptr(p1.get());
    return 0;
}
```

`get()`返回的指针所对应的内存空间，会在最后一个智能指针被销毁时所释放。

`std::shared_ptr::get`函数有多个陷阱需要规避，包括：

* 不使用`get()`的返回值来初始化或`reset()`另一个智能指针；
* 不能 delete `get()`返回的指针；



**Demo5-2 std::shared_ptr::get** 错误用例1

```c++
#include <memory>
#include <iostream>

int main()
{
	std::shared_ptr<int> p = std::make_shared<int>(10);
	std::cout << *p << std::endl;  // 10

	int *pg = p.get();
	{
		std::shared_ptr<int> q(pg);
	} // q 被销毁

	std::cout << *p << std::endl;   // pointer being freed was not allocated
									                // 报错， p 所指向的内存资源已被释放

	return 0;
} 
```

Demo 5-2 中创建了两个智能指针`p`和 `q`，它们指向相同的内存空间，但是由于它们是相互独立创建的，所以各自的引用计数都是1。当`q`离开作用域时，调用相应的析构函数，`q`所对应的内存资源被释放，从而`p`变成了一个空悬指针(`dangling pointer`)。



**Demo 5-3 std::shared_ptr::get** 错误用例2

```c++
#include <memory>
#include <iostream>

int main()
{
	std::shared_ptr<int> p = std::make_shared<int>(10);
	std::cout << *p << std::endl;  // 10

	int *pg = p.get();
	delete pg;  // p 所对应的内存空间已被释放

	return 0;
} // 报错: pointer being freed was not allocated
  // !!! 此时智能指针 p 的引用计数是1，所以会尝试释放内存空间。
  // !!! 不能释放一个未分配资源的内存空间，会引发各种难以想象的错误。

```

不能 `delete` 由`std::shared_ptr::get` 返回的指针。



### 判断智能指针是否为空

```c++
explicit operator bool() const noexcept;
```

Return value:

* `false` if the shared_ptr is a null pointer;
* `true` otherwise.



**Demo 5 std::shared_ptr::operator bool**

```c++
#include <iostream>
#include <memory>

int main ()
{
  std::shared_ptr<int> foo;
  std::shared_ptr<int> bar (new int(34));

  if (foo) std::cout << "foo points to " << *foo << '\n';
  else std::cout << "foo is null\n";

  if (bar) std::cout << "bar points to " << *bar << '\n';
  else std::cout << "bar is null\n";

  return 0;
}
```



### 重置指针

```c++
void reset() noexcept;
```

重置指针，使得`shared_ptr` 变为空。



```c++
template<class U>
void reset(U* p);
```

重置指针，使得`shared_ptr`指向`p`，`use_count`变为1。



```c++
// pointer + deleter
template<class U, class D>
void reset(U* p, D del);
```

重置指针，使得`shared_ptr`指向`p`，`use_count`变为1。



```c++
// pointer + deleter + allocator
template<class U, class D, class Alloc>
void reset(U* p, D del, Alloc alloc);
```

重置指针，使得`shared_ptr`指向`p`，`use_count`变为1。



**Demo5 std::shared_ptr::reset**

```c++
#include <iostream>
#include <memory>

int main()
{
	std::shared_ptr<int> sp;  // empty pointer

	// takes ownership of pointer
	sp.reset(new int);
	*sp = 10;
	std::cout << *sp << std::endl;

	// deletes managed object, acquires new pointer.
	sp.reset(new int);
	*sp = 20;
	std::cout << *sp << std::endl;
  
	// deletes managed object
	sp.reset();
  
	return 0;
}
```



### 引用计数

```c++
bool unique() const noexcept;
```

引用计数是否为1。



**Demo6 std::shared_ptr::unique**

```c++
#include <iostream>
#include <memory>

int main ()
{
  std::shared_ptr<int> foo;
  std::shared_ptr<int> bar (new int);

  std::cout << "foo unique?\n" << std::boolalpha;
  std::cout << "1: " << foo.unique() << '\n';  // false (empty)

  foo = bar;
  std::cout << "2: " << foo.unique() << '\n';  // false (shared with bar)

  bar = nullptr;
  std::cout << "3: " << foo.unique() << '\n';  // true

  return 0;
}
```



## 智能指针与自定义 deleter

默认情况下，`shared_ptr`假定它们指向的是由`new`分配的动态内存。因此当`shared_ptr`被销毁时，它默认地对它管理的指针进行`delete`操作。

当智能指针管理的资源不是由`new`分配的内存，记住传递给它一个删除器(`deleter`)。

```c++
#include <iostream>
#include <memory>

class sample
{
public:
	sample() 
	{ 
		std::cout << "Call constructor." << std::endl;
		data = new int [10]; 
	}
	~sample() 
	{ 
		std::cout << "Call Destructor." << std::endl;
	}

	int* data;
};

void deleter(sample *sp)
{
	std::cout << "Call deleter." << std::endl;
	delete [] sp->data;
}

int main()
{
  sample a;
	std::shared_ptr<sample> sp1(&a);           // Call Destructor to free memory，内存泄漏
	std::shared_ptr<sample> sp2(&a, deleter);  // Call deleter to free memory，完好释放数组空间
	return 0;
}
```



## unique_ptr

`unique_ptr` 负责指针的存储，提供有限的垃圾回收的功能。`unique_ptr`独占其指向的对象。

### unique_ptr 的构造函数

```c++
// default constructor
constexpr unique_ptr() noexcept;

// construct from pointer
explicit unique_ptr(pointer p) noexcept;
```



## weak_ptr

`weak_ptr`是一种不控制所指向对象生存期的智能指针，它指向一个由`shared_ptr`管理的对象。将一个 `weak_ptr` 绑定到一个 `shared_ptr` 不会改变 `shared_ptr` 的引用计数。一旦最后一个指向对象的 `shared_ptr` 被销毁，对象就会被释放。因此，`weak_ptr` 的名称正是匹配了这种智能指针"弱"共享对象的特点。



### 构造函数

```c++
// default constructor
constexpr weak_ptr() noexcept;

// copy constructor
template<class U>
weak_ptr(const weak_ptr<U>& x) noexcept;

// from shared_ptr
template<class U>
weak_ptr(const shared_ptr<U>& x) noexcept;
```

**Demo - weak_ptr 的构造函数**

```c++
#include <iostream>
#include <memory> 

int main()
{
	std::shared_ptr<int> sp = std::make_shared<int>(10);

	// constexpr weak_ptr() noexcept;
	std::weak_ptr<int> wp1;

	// template<typename U>
	// weak_ptr(const weak_ptr<U>& x) noexcept;
	std::weak_ptr<int> wp2(wp1);

	// template<typename U>
	// weak_ptr(const shared_ptr<U>& x) noexcept;
	std::weak_ptr<int> wp3(sp);

	std::cout << "Use count:" << std::endl;
	std::cout << "wp1: " << wp1.use_count() << std::endl;  // 0
	std::cout << "wp2: " << wp2.use_count() << std::endl;  // 0
	std::cout << "wp3: " << wp3.use_count() << std::endl;  // 1

	return 0;
}
```



### 拷贝赋值函数

```c++
// copy assignment
template<class U>
weak_ptr<U>& operator=(const weak_ptr<U>& x) noexcept;

// copy assignment from shared_ptr
template<class U>
weak_ptr<U>& operator=(const shared_ptr<U>& x) noexcept;
```



### 成员函数

| 成员函数                                                    | 作用                                                         |
| ----------------------------------------------------------- | ------------------------------------------------------------ |
| `template<typename U> shared_ptr<U> lock() const noexcept;` | 由于`weak_ptr`所指向的对象有可能不存在，因此不能直接使用`weak_ptr`访问对象，而必须调用`lock()`成员函数。如果`weak_ptr`所指向的对象非空，且相应的`shared_ptr`的引用计数非0，则返回此`shared_ptr`，否则返回一个空的`shared_ptr`。 |
| `long int use_count() noexcept;`                            | 与此`weak_ptr`指向相同对象的`shared_ptr`的引用计数。         |
| `bool expired() const noexcept;`                            | 作用等同于判断`use_count() == 0`，但效率更高。当`weak_ptr`为空，或者所绑定的`shared_ptr`已经释放，则返回true。 |
| `void reset() noexcept;`                                    | 重置指针，变为空。                                           |



**Demo - std::weak_ptr::lock**

获取 `weak_ptr` 所绑定的`shared_ptr`。

```c++
#include <iostream>
#include <memory>

int main()
{
	std::shared_ptr<int> sp1, sp2;
	std::weak_ptr<int> wp;

	if(!wp.lock())
		std::cout << "The weak_ptr is empty or expired." << std::endl;  // The weak_ptr is empty or expired.
	else
	{
		sp2 = wp.lock();
		std::cout << "wp: " << *sp2 << std::endl;
	}

	sp1 = std::make_shared<int>(10);
	wp = sp1;
	if(!wp.lock())
		std::cout << "The weak_ptr is empty or expired." << std::endl;
	else
	{
		sp2 = wp.lock();
		std::cout << "wp: " << *sp2 << std::endl;  // wp: 10
	}		

	return 0;
}
```



**Demo - std::weak_ptr::reset**

重置指针，变为空。

```c++
#include <iostream>
#include <memory>

int main()
{
  std::shared_ptr<int> sp = std::make_shared<int>(10);
  std::weak_ptr<int> wp(sp);
  std::cout << "wp " << (wp.expired() ? "is" : "is not") << " expired." << std::endl;

  wp.reset();
  std::cout << "wp " << (wp.expired() ? "is" : "is not") << " expired." << std::endl;

  return 0;
}
```

