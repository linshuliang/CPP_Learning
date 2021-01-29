# C++ 内存管理标准库

在C++中，内存分成5个区，他们分别是堆、栈、自由存储区、全局/静态存储区和常量存储区。

* 栈：在执行函数时，函数内局部变量的存储单元都可以在栈上创建，函数执行结束时这些存储单元自动被释放。栈内存分配运算内置于处理器的指令集中，效率很高，但是分配的内存容量有限。
* 堆：就是那些由 `new`分配的内存块，他们的释放编译器不去管，由我们的应用程序去控制，一般一个`new`就要对应一个 `delete`。如果程序员没有释放掉，那么在程序结束后，操作系统会自动回收。
* 自由存储区：就是那些由 `malloc` 分配的内存块，用 `free` 来释放。
* 全局/静态存储区：全局变量和静态变量被分配到同一块内存中。
* 常量存储区 ：这是一块比较特殊的存储区，里面存放的是常量，不允许修改。



**内存空间与变量类型的对应关系**：

* 静态内存用来保存局部`static`对象，类`static`数据成员，以及全局变量；
* 栈内存用来保存定义在函数内的非`static`对象；
* 程序用堆来存储动态分配的对象；
* 常量被放在常量存储区中；



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
* `weak_ptr`     : 一种弱引用，指向 `shared_ptr` 所管理的对象。



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



## 2 std::shared_ptr

c++ 中动态内存的管理是通过`new`和`delete`来完成的，只要保证`new`和`delete`的配对使用，是没有问题的。但是有时候我们会忘记释放内存，甚至有时候我们根本就不知道什么时候释放内存。特别是在多个线程间共享数据时，更难判断内存该何时释放。这种情况下机器就容易产生引用非法内存的指针。

`std::shared_ptr` 用于管理指针的存储，提供有限的`垃圾收集(garbage collection)`的功能，并可能与其他对象共享管理权。



**std::shared_ptr 的部分代码**

```c++
template <class _Ty>
class _Ptr_base { // base class for shared_ptr and weak_ptr
public:
    _Ptr_base(const _Ptr_base&) = delete;  // 阻止拷贝
    _Ptr_base& operator=(const _Ptr_base&) = delete;  // 阻止赋值

private:
    element_type* _Ptr{nullptr};     // 存储指针（stored pointer）
    _Ref_count_base* _Rep{nullptr};  // 引用计数管理类

    friend shared_ptr<_Ty>;
};
```



## 2-1 shared_ptr 的引用计数

每个`shared_ptr`都有与指向对象关联的计数器，通常称其为`引用计数(reference count)`。

下面的操作，会使得计数器递增：

* 拷贝构造 (copy constructor)
* 拷贝赋值 (copy assignment)
* 将`shared_ptr `对象作为函数的参数
* 将`shared_ptr`对象作为函数的返回值

下面的操作，会使得计数器递减：

* `shared_ptr` 对象被销毁
* `shared_ptr` 对象被赋予新值

```c++
std::shared_ptr<int> r = std::make_shared<int>(50);
r = q;  // 给 r 赋值
		// 递增 q 指向对象的引用计数
		// 递减 r 原来指向对象的引用计数
		// 如果 r 原来指向对象的引用计数为0，则自动释放该对象
```

**注意：** 只有用一个`shared_ptr`为另一个`shared_ptr`赋值时，才将这两个指针关联起来，直接使用地址值会导致各个`shared_ptr`独立。



### 2-2 std::shared_ptr 类的构造函数

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
// The object acquires the content managed by x including its owned pointer,
// x 的引用计数是多少， 新的 shared_ptr 的引用计数就是多少，
// x becomes an empty object (as if default-constructed)
template<typename U>
shared_ptr(shared_ptr<U>&& x) noexcept;

// copy from weak_ptr
template<typename U>
explicit shared_ptr(const weak_ptr<U>& x);
// If x is not empty, the object shares ownership of x's assets and increases the use_count by 1.
// If x is empty, an empty object is constructed (the same as default constructer).
// If x has expired, a bad_weak_ptr exception is thrown.

// move from unique_ptr
// The object acquires the content managed by x including its owned pointer,
// x becomes an empty object.
template<typename U, typename D>
shared_ptr(unique_ptr<U, D>&& x);

// aliasing constructor
// the object co-owns x's managed object and counts as one additional use of x. 
// However, the stored value is p, without managing its storage. 
// 此构造函数生成的 shared_ptr 的类型为： shared_ptr<element_type>
template<class U>
shared_ptr(const shared_ptr<U>& x, element_type* p) noexcept;
```

**shared_ptr 构造函数 Demo**

```c++
// shared_ptr constructor example
#include <iostream>
#include <memory>

struct C { int* data; };

void main() 
{
	// default constructor
	// constexpr shared_ptr() noexcept;
	std::shared_ptr<int> p1;

	// from null pointer
	// constexpr shared_ptr(nullptr_t) : shared_ptr() {}
	std::shared_ptr<int> p2(nullptr);

	// from pointer
	// template<class U>
	// explict shared_ptr(U* p);
	std::shared_ptr<int> p3(new int);

	// pointer + deleter
	// template<class U, class D>
	// shared_ptr(U* p, D del)
	std::shared_ptr<int> p4(new int, std::default_delete<int>());
	
	// pointer + deleter + allocator
	// template<class U, class D, class Alloc>
	// shared_ptr(U* p, D del, Alloc alloc>
	std::shared_ptr<int> p5(new int, [](int* p) {delete p;}, std::allocator<int>());
	
	// copy constructor
	// template<class U>
	// shared_ptr(const shared_ptr<U>& x) noexcept;
	std::shared_ptr<int> p6(p5);

	// move constructor
	// template<class U>
	// shared_ptr(shared_ptr<U>&& x) noexcept;
	std::shared_ptr<int> p7(std::move(p6));

	// template<class U>
	// shared_ptr(unique_ptr<U>& x);
	std::shared_ptr<int> p8(std::unique_ptr<int>(new int));

	std::shared_ptr<C> obj(new C);
	obj->data = new int(10);
	int* one_int = new int(20);

	// aliasing constructor
	// template<class U>
	// shared_ptr(const shared_ptr<U>& x, element_type* p) noexcept;
	std::shared_ptr<int> p9(obj, one_int);

	std::cout << "use_count:\n";
	std::cout << "p1: "  << p1.use_count()  << '\n';  // 0
	std::cout << "p2: "  << p2.use_count()  << '\n';  // 0
	std::cout << "p3: "  << p3.use_count()  << '\n';  // 1
	std::cout << "p4: "  << p4.use_count()  << '\n';  // 1
	std::cout << "p5: "  << p5.use_count()  << '\n';  // 2
	std::cout << "p6: "  << p6.use_count()  << '\n';  // 2 -> 0
	std::cout << "p7: "  << p7.use_count()  << '\n';  // 2
	std::cout << "p8: "  << p8.use_count()  << '\n';  // 1
	std::cout << "obj: " << obj.use_count() << '\n';  // 2
	std::cout << "p9: "  << p9.use_count()  << '\n';  // 2
	std::cout << "*p9: " << *p9             << '\n';  // 20
	delete p9.get();  // 因为 p9 不管理 one_int 的生存期，所以必须显式删除
}
```

#### 2-2-1 std::make_shared

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

void main()
{
  // 指向 int 的智能指针
  std::shared_ptr<int> foo = std::make_shared<int> (10);
  
  // 指向 std::string 的智能指针
  std::shared_ptr<std::string> bar = std::make_shared<std::string>(6, '2');
  
  // 指向 std::pair<int, int> 的智能指针
  std::shared_ptr<std::pair<int, int>> baz = std::make_shared<std::pair<int, int>> (30, 50);
  
  std::cout << "*foo: " << *foo << std::endl;  // 10
  std::cout << "*bar: " << *bar << std::endl;  // "222222"
  std::cout << "*baz: " << baz->first << ", " << baz->second << std::endl;  // 30, 50
}
```



## 2-3 析构函数 

```c++
~shared_ptr();
```

`shared_ptr`的析构函数会递减它所指向的对象的引用计数。如果引用计数变为`0`，那么`shared_ptr`的析构函数就会销毁对象，并释放它占用的内存。

**shared_ptr 析构函数 Demo**

```c++
#include <iostream>
#include <memory>

void main()
{
	auto myDeleter = [](int* p)
	{
		std::cout << "Call deleter" << std::endl;
		delete p;
	};

	{
		std::shared_ptr<int> var(new int{ 10 }, myDeleter);
		std::cout << "*var = " << *var << std::endl;
	} // var 离开作用域，执行析构函数

	std::cout << "Main End" << std::endl;
}
```

#### 2-3-1 智能指针与自定义 deleter

默认情况下，`shared_ptr`假定它们指向的是由`new`分配的动态内存。因此当`shared_ptr`被销毁时，它默认对管理的指针进行`delete`操作。

当智能指针管理的资源不是由`new`分配的内存（比如类调用构造函数），记住传递给它一个删除器(`deleter`)，。

```c++
// shared_ptr destructor demo : customized deleter
#include <iostream>
#include <memory>

class sample
{
public:
	sample()
	{
		std::cout << "Call constructor." << std::endl;
		data = new int[10];
	}

	~sample()
	{
		std::cout << "Call Destructor." << std::endl;
	}
    
private:
	int* data;
};

// 一般而言，deleter的返回值类型为void，形参类型为data_type*
void deleter(sample* sp)
{
	std::cout << "Call deleter." << std::endl;
	delete[] sp->data;
}

void main()
{
	std::shared_ptr<sample> sp1(new sample());           // Call Destructor to free memory，内存泄漏
	std::shared_ptr<sample> sp2(new sample(), deleter);  // Call deleter to free memory，正确释放数组空间
}
```



### 2-4 赋值函数

#### 2-4-1 拷贝赋值函数

```c++
// The copy assignments adds the object as a shared owner of x's assets, increasing their use_count.
template<class U>
shared_ptr& operator=(const shared_ptr<U>& x) noexcept;
```

#### 2-4-2 移动赋值函数

```c++
// The move assignments transfer ownership from x to the shared_ptr object without altering the use_count. 
// x becomes an empty shared_ptr (as if default-constructed).
template<class U>
shared_ptr& operator=(shared_ptr<U>&& x) noexcept;
```

#### 2-4-3 转移控制权

```c++
// the move assignments from other managed pointer types also transfer ownership
// and are initialized with set a use_count of 1.
template<class U, class D>
shared_ptr& operator=(unique_ptr<U, D>&& x);
```

**shared_ptr 赋值函数 Demo**

```c++
#include <iostream>
#include <memory>

void main() 
{
	std::shared_ptr<int> foo;
	std::shared_ptr<int> bar(new int(10));

	// copy assignment
	// template<class U>
	// shared_ptr& operator=(const shared_ptr<U>& x) noexcept;
	foo = bar; 

	// copy assignment
	// template<class U>
	// shared_ptr& operator=(const shared_ptr<U>& x) noexcept;
	bar = std::make_shared<int>(20);
	std::cout << "*bar: " << *bar << '\n';
	std::cout << "bar.use_count(): " << bar.use_count() << '\n';  // 1

	std::unique_ptr<int> up(new int(30));

	// move from other pointer
	// template<class U>
	// shared_ptr& operator=(unique_ptr<U>&& x);
	foo = std::move(up);

	std::cout << "*foo: " << *foo << '\n';
	std::cout << "foo.use_count(): " << foo.use_count() << std::endl;  // 1
}
```



### 2-5 解引用

#### 2-5-1 解引用指针对象

```c++
element_type& operator*() const noexcept;
```

#### 2-5-2 解引用指针对象的成员变量

```c++
element_type& operator->() const noexcept;
```

**shared_ptr 解引用 Demo**

```c++
#include <iostream>
#include <memory>

struct cla
{
	int a;
	int b;
};

void main()
{
	std::shared_ptr<int> foo1(new int);
	std::shared_ptr<int> bar1(new int (10));
	*foo1 = *bar1 * 2;
	std::cout << "*foo1: " << *foo1 << std::endl;  // 20
	std::cout << "*bar1: " << *bar1 << std::endl;  // 10
    
    std::shared_ptr<cla> foo;
	std::shared_ptr<cla> bar (new cla);
    
	// template<typename U>
	// shared_ptr& operator=(const shared_ptr<U>&);
	foo = bar;
    
	foo->a = 10;
	bar->b = 20;
	if(foo) std::cout << "foo: " << foo->a << " " << foo->b << std::endl;  // 10, 20
	if(bar) std::cout << "bar: " << bar->a << " " << bar->b << std::endl;  // 10, 20
}
```



### 2-6 std::shared_ptr 的成员函数

| 成员函数名        | 作用                                                         |
| ----------------- | ------------------------------------------------------------ |
| `swap()`          | 交换。包括数据和引用计数。                                   |
| `reset()`         | 重置指针。Reset pointer.                                     |
| `get()`           | 返回存储指针。Returns the *stored pointer*.                  |
| `use_count()`     | 引用计数。Returns the number of `shared_ptr` objects that share ownership over the same pointer. |
| `unique()`        | 引用计数是否为1。Returns whether the `shared_ptr` object does not share ownership over its pointer with other `shared_ptr` objects. |
| `operator bool()` | 是否为空。Returns whether the stored pointer is a null pointer. |



#### 2-6-1 交换管理对象

```c++
// Exchanges the contents of the shared_ptr object with those of x,
// transferring ownership of any managed object between them without destroying or altering the use count of either.
void swap(shared_ptr& x) noexcept;

// 伪代码
template<class T>
std::shared_ptr<T>::swap(shared_ptr<T>& x) noexcept
{
    // 数据替换
    T temp = *this;
    *this = *x;
    *x = temp;
    
    // 引用计数替换
    int temp_count = this.use_count;
    this.use_count = x.use_count;
    x.use_cout = temp_count;
}
```

**shared_ptr 交换 demo**

```c++
#include <iostream>
#include <memory>

void main()
{
	std::shared_ptr<int> foo(new int{ 20 });
	std::shared_ptr<int> foo2 = foo;
	std::shared_ptr<int> bar(new int{ 10 });
	foo.swap(bar);
	std::cout << *foo << ", " << foo.use_count() << std::endl;  // 10, 1
	std::cout << *bar << ", " << bar.use_count() << std::endl;  // 20, 2
}
```



#### 2-6-2 重置指针

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

**std::shared_ptr 重置 demo**

```c++
#include <iostream>
#include <memory>

void main()
{
	std::shared_ptr<int> sp;  // empty pointer

	// takes ownership of pointer
	sp.reset(new int);
	*sp = 10;
	std::cout << *sp << std::endl;  // 10

	// deletes managed object, acquires new pointer.
	sp.reset(new int {20});
	std::cout << *sp << std::endl;  // 20
  
	// deletes managed object
	sp.reset();
}
```



#### 2-6-3 获取存储指针

```c++
element_type* get() const noexcept;
// Returns the stored pointer
// The stored pointer points to the object the shared_ptr object dereferenced to.
// 也就是说 *sp = *sp.get();
// 注意： shared_ptr 的存储指针和管理的对象不一定相同，例如 alias constructor 创建的 shared_ptr。
```

智能指针提供`get()`成员函数的出发点：我们向不能使用智能指针的代码传递一个内置指针。

```c++
// std::shared_ptr::get() demo 
#include <iostream>
#include <memory>
using namespace std;

void useShared_ptr(int *p)
{
    cout<< *p << endl;
}

void main()
{
    shared_ptr<int> p1 = make_shared<int>(32);
    useShared_ptr(p1.get());
}
```

##### shared_ptr::get 错误用法

`get()`返回的指针所对应的内存空间，会在最后一个智能指针被销毁时所释放。

`std::shared_ptr::get`函数有多个陷阱需要规避，包括：

* 不使用`get()`的返回值来初始化或`reset()`另一个智能指针；
* 不能 delete `get()`返回的指针；

```c++
// std::shared_ptr::get 错误用例 -- 不使用std::shared_ptr::get() 的返回值来初始化或reset()另一个智能指针。
#include <memory>
#include <iostream>

void main()
{
	std::shared_ptr<int> p = std::make_shared<int>(10);
	std::cout << *p << std::endl;  // 10

	int *pg = p.get();
	{
		std::shared_ptr<int> q(pg);
	} // q 被销毁, pg 内存空间被释放
    
	std::cout << *p << std::endl;  // 报错， p 所指向的内存资源已被释放
}

/*
两个智能指针 p 和 q，它们指向相同的内存空间，但是由于它们是相互独立创建的，所以各自的引用计数都是1。
当 q 离开作用域时，调用相应的析构函数，q 所对应的内存资源被释放，从而 p 变成了一个空悬指针(dangling pointer)。
*/
```

```c++
// std::shared_ptr::get 错误用例 -- 不能 `delete` 由`std::shared_ptr::get` 返回的指针。
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



#### 2-6-4 判断智能指针是否为空

```c++
explicit operator bool() const noexcept;
```

Return value:

* `false` if the shared_ptr is a null pointer;
* `true` otherwise.

```c++
// Demo : std::shared_ptr::operator bool
#include <iostream>
#include <memory>

void main ()
{
  std::shared_ptr<int> foo;
  std::shared_ptr<int> bar (new int(34));

  if (foo) std::cout << "foo points to " << *foo << '\n';
  else std::cout << "foo is null\n";

  if (bar) std::cout << "bar points to " << *bar << '\n';
  else std::cout << "bar is null\n";
}
```



#### 2-6-5 引用计数是否为1

```c++
bool unique() const noexcept;
```

`shared_ptr.use_count()  == 1` 等同于 `shared_ptr.unique()`，但`std::shared_ptr::unique()`的效率更高。 

```c++
// Demo: std::shared_ptr::unique
#include <iostream>
#include <memory>

void main ()
{
  std::shared_ptr<int> foo;
  std::shared_ptr<int> bar (new int);

  std::cout << "foo unique?\n" << std::boolalpha;
  std::cout << "1: " << foo.unique() << '\n';  // false (empty)

  foo = bar;
  std::cout << "2: " << foo.unique() << '\n';  // false (shared with bar)

  bar = nullptr;
  std::cout << "3: " << foo.unique() << '\n';  // true
}
```



## 3 unique_ptr

`unique_ptr` 负责指针的存储，提供有限的垃圾回收的功能。`unique_ptr`独占其指向的对象。

### 3-1 unique_ptr 的构造函数

``` c++
// default constructor
constexpr unique_ptr() noexcept;

// construct from pointer
explicit unique_ptr(pointer p) noexcept;

// move constructor（移动构造函数）
// 当前unique_ptr获取x管理的内容，x的引用计数变为0，当前unique_ptr的引用计数变为1。
unique_ptr(unique_ptr&& x) noexcept;

// copy constructor (禁止拷贝)
unique_ptr(const unique_ptr&) = delete;
```



### 3-2 unique_ptr 的赋值函数

```c++
// move assignment
unique_ptr& operator=(unique_ptr&& x) noexcept;

// assign null pointer
unique_ptr& operator=(nullptr) noexcept;

// copy assignment (禁止拷贝)
unique_ptr& operator=(const unique_ptr&) = delete;
```

The object acquires the ownership of `x's` content, including both the stored pointer and the stored `deleter` (along with the responsibility of deleting the object at some point). Any object owned by the `unique_ptr` object before the call is deleted.

```c++
#include <iostream>
#include <memory>

void main()
{
	std::unique_ptr<int> foo;
	std::unique_ptr<int> bar;

	// unique_ptr& operator=(unique_ptr&&);
	foo = std::unique_ptr<int>(new int(100));

	// unique_ptr& operator=(unique_ptr&&);
	bar = std::move(foo);

	if (foo)
		std::cout << "foo : " << *foo << std::endl;
	else
		std::cout << "foo is empty" << std::endl;  // 赋值后，变为空

	if (bar)
		std::cout << "bar : " << *bar << std::endl;  // 被赋值的变量，管理相应的指针
	else

		std::cout << "bar is empty" << std::endl;
}
```



### 3-3 unique_ptr 的成员函数

| 成员函数名 | 作用                                                         |
| ---------- | ------------------------------------------------------------ |
| `get`      | 返回 `unique_ptr` 管理的指针                                 |
| `reset`    | 重置指针                                                     |
| `release`  | Release ownership of its stored pointer, by returning its value and replacing it with a null pointer. 释放所管理指针的控制权，并返回管理的指针。 |
| `swap`     | 交换管理的对象。                                             |



```c++
pointer get() const noexcept;
```

Returns the stored pointer. The stored pointer points to the object managed by the `unique_ptr`, if any, or to `nullptr` if the `unique_ptr` is empty.

Notice that a call to this function does not make `unique_ptr` release ownership of the pointer (i.e., it is still responsible for deleting the managed data at some point). Therefore, the value returned by this function shall not be used to construct a new managed pointer.

**Return Value** : A pointer  to the managed object, or a null pointer.  `pointer` is a member type, defined as the pointer type that points to the type of object managed.



```c++
void reset(pointer p = pointer()) noexcept;
```

Destroys the object currently managed by the `unique_ptr` and takes ownership of `p`.

If `p` is a null `poniter` (such as a default-initialized pointer), the `unique_ptr` becomes empty,  managing no object after the call.

```c++
// unique_ptr Reset Demo
#include <iostream>
#include <memory>

void main()
{
	std::unique_ptr<int> up;  // empty
	up.reset(new int);        // takes ownership of pointer
	*up = 5;
	std::cout << *up << std::endl;

	up.reset(new int);  // deletes managed object, acquire new pointer
	*up = 10;
	std::cout << *up << std::endl;

	up.reset();
}
```



```c++
pointer release() noexcept;
```

Release ownership of its stored pointer, by returning its value and replacing it with a null pointer.

The call does not destroy the managed object, but the `unique_ptr` object is released from the responsibility of deleting the object. Some other entity must take responsibility for deleting the object at some point.

To force the destruction of the object pointed, either use member function `reset` or perform an `assignment operation` on it.

**Return Value**: A pointer to the object managed by `unique_ptr` before the call. `pointer` is a member type, defined as the pointer type that points to the type of object managed.

```c++
#include <iostream>
#include <memory>

void main()
{
	std::unique_ptr<int> up(new int);
	*up = 10;

	int* manual_pointer = up.release();  // 此时 up 将释放控制权，manual_pointer 接管指针的控制权
	std::cout << "The stored value of manual_pointer : " << *manual_pointer << std::endl;
	delete manual_pointer;  // new 出来的内存必须显示删除，否则将导致内存泄漏
}
```



```c++
void swap(unique_ptr& x) noexcept;
```

Exchanges the contents of the `unique_ptr` object with those of x, transferring ownership of any managed object between them without destroying either. 

```c++
#include <iostream>
#include <memory>

void main()
{
	std::unique_ptr<int> foo(new int{ 10 });
	std::unique_ptr<int> bar(new int{ 20 });

	foo.swap(bar);

	std::cout << "foo : " << *foo << std::endl;  // 20
	std::cout << "bar : " << *bar << std::endl;  // 10
}
```



### 3-4 unique_ptr 的优点

`unique_ptr` 是非常轻量的封装，存储空间几乎等于裸指针，但安全性得到了极大的强化。实际中，需要共享所有权的对象是比较少的，但需要转移所有权是非常常见的情况。 `unique_ptr`  配合移动语义即可轻松解决所有权传递的问题。



## 4 weak_ptr

`weak_ptr`是一种不控制所指向对象生存期的智能指针，它指向一个由`shared_ptr`管理的对象。将一个 `weak_ptr` 绑定到一个 `shared_ptr` 不会改变 `shared_ptr` 的引用计数。一旦最后一个指向对象的 `shared_ptr` 被销毁，对象就会被释放。因此，`weak_ptr` 的名称正是匹配了这种智能指针"弱"共享对象的特点。



### 4-1 构造函数

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

void main()
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
}
```



### 4-2 拷贝赋值函数

```c++
// copy assignment
template<class U>
weak_ptr<U>& operator=(const weak_ptr<U>& x) noexcept;

// copy assignment from shared_ptr
template<class U>
weak_ptr<U>& operator=(const shared_ptr<U>& x) noexcept;
```



### 4-3 成员函数

| 成员函数      | 作用                                                         |
| ------------- | ------------------------------------------------------------ |
| `lock() `     | 由于`weak_ptr`所指向的对象有可能不存在，因此不能直接使用`weak_ptr`访问对象，而必须调用`lock()`成员函数。如果`weak_ptr`所指向的对象非空，且相应的`shared_ptr`的引用计数非0，则返回此`shared_ptr`，否则返回一个空的`shared_ptr`。 |
| `use_count()` | 与此`weak_ptr`指向相同对象的`shared_ptr`的引用计数。         |
| `expired()`   | 作用等同于判断`use_count() == 0`，但效率更高。当`weak_ptr`为空，或者所绑定的`shared_ptr`已经释放，则返回`true`。 |
| `reset();`    | 重置指针，变为空。                                           |



**Demo - std::weak_ptr::lock**

获取 `weak_ptr` 所绑定的`shared_ptr`。

```c++
#include <iostream>
#include <memory>

template<class T>
void acess_weak_ptr(const std::weak_ptr<T>& wp)
{
    std::shared_ptr<T> sp = wp.lock();
	if (!sp)
		std::cout << "The weak_ptr is empty or expired." << std::endl;
	else
		std::cout << "contained value : " << *sp << std::endl;
}

void main()
{
	std::shared_ptr<int> sp1, sp2;
	std::weak_ptr<int> wp;
	acess_weak_ptr<int>(wp);

	sp1 = std::make_shared<int>(10);
	wp = sp1;
	acess_weak_ptr<int>(wp);
}
```



**Demo - std::weak_ptr::reset**

重置指针，变为空。

```c++
#include <iostream>
#include <memory>

void main()
{
  std::shared_ptr<int> sp = std::make_shared<int>(10);
  std::weak_ptr<int> wp(sp);
  std::cout << "wp " << (wp.expired() ? "is" : "is not") << " expired." << std::endl;  // is not expired

  wp.reset();
  std::cout << "wp " << (wp.expired() ? "is" : "is not") << " expired." << std::endl;  // is expired
}
```



### 4-4 weak_ptr 的作用

#### 4-4-1 弱引用 weak_ptr 解决 shared_ptr 的循环引用

引用计数是一种便利的内存管理机制，但它有一个很大的缺点，就是不能管理循环引用的对象。

```c++
// shared_ptr 循环引用会导致内存泄漏
#include <iostream>
#include <memory>

class parent;
class children;

class parent
{
public:
	~parent() { std::cout << "[Parent] Call Destructor" << std::endl; }

public:
	std::shared_ptr<children> children_;
};

class children
{
public:
	~children() { std::cout << "[Children] Call Destructor" << std::endl; }

public:
	std::shared_ptr<parent> parent_;
};

void main()
{
	std::shared_ptr<parent> p(new parent());
	std::shared_ptr<children> c(new children());

	p->children_ = c;
	c->parent_ = p;

	std::cout << "p.use_count() = " << p.use_count() << std::endl;  // 2
	std::cout << "c.use_count() = " << c.use_count() << std::endl;  // 2
}  // 程序退出，p 和 c 的引用计数仍为1，不能自动释放，造成内存泄漏

/* 程序输出
p.use_count() = 2
c.use_count() = 2
*/
```



`weak_ptr` 是一种不控制所指向对象生存周期的指针，它指向一个由`shared_ptr`所管理的对象。在功能上，`weak_ptr`与普通指针类似。`weak_ptr`与普通指针的重大区别在于：`weak_ptr`能检测到所管理的对象是否已经被释放，从而避免访问非法内存。

```c++
// 使用 weak_ptr 解决 shared_ptr 无法循环引用的问题
#include <iostream>
#include <memory>

class parent;
class children;

class parent
{
public:
	~parent() { std::cout << "[Parent] Call Destructor" << std::endl; }

public:
	std::weak_ptr<children> children_;
};

class children
{
public:
	~children() { std::cout << "[Children] Call Destructor" << std::endl; }

public:
	std::weak_ptr<parent> parent_;
};

void main()
{
	std::shared_ptr<parent> p(new parent());
	std::shared_ptr<children> c(new children());

	p->children_ = c;
	c->parent_ = p;

	std::cout << "p.use_count() = " << p.use_count() << std::endl;  // 1
	std::cout << "c.use_count() = " << c.use_count() << std::endl;  // 1
}  // 程序退出，p 和 c 的引用计数变为0，自动释放

/* 程序输出
p.use_count() = 1
c.use_count() = 1
[Children] Call Destructor
[Parent] Call Destructor
*/
```



## 5 `std::allocator`

`new` 有一些灵活性上的局限，其中一方面表现在：它将内存分配和对象构造组合在一起。类似的，`delete`将对象析构和内存释放组合在一起。

* 分配单个对象时，通常希望将内存分配和对象初始化组合在一起，在这种情况下，肯定知道对象有什么值；

* 分配一大块内存时，通常计划在这块内存上按需构造对象，在这种情况下，我们可以将内存分配和对象构造分离。也就是先分配一大块内存，在需要时才执行对象创建操作。

  

```c++
// new 的局限
#include <iostream>
#include <string>

void main()
{
	int n = 100;
	std::string* const p = new std::string[n];
	std::string* q = p;

	std::cout << "Input string (end with 'Enter') : " << std::endl;
	std::string s;
	while (std::cin >> s && q != p + n)  // 按下 Ctrl + Z 组合键，再按 Enter, 此时 std::cin >> s 返回 false
	{
		*q = s;
		q++;
	}

	std::cout << "All string : " << std::endl;
	const size_t size = q - p;
	for (int i = 0; i < size; i++)
	{
		std::cout << p[i] << std::endl;
	}
	
	delete[] p;
}
```

`new` 表达式分配并初始化了`n`个`string`，但是，我们可能不需要 `n` 个 `string`，那么就可能创建了一些永远也用不到的对象。更为糟糕的是，那么确实要用到的对象，我们在初始时立即赋予了新值，使用时又需再次赋值，也就是赋值了两次。



**Allocators** are classes that define memory models to be used by some parts of the standard library, and most specifically, by `STL containers`.

`std::allocator` is the allocator that all standard containers will use if their last template parameter is not specified, and is the only predefined allocator in the standard library.



### 5.1 构造函数

```c++
// default constructor
allocator() noexcept;

// copy constructor
allocator(const allocator& alloc) noexcept;
```

The `std::allocator` has no data members, it is not required to perform any initialization.



### 5.2 析构函数

```c++
~allocator();
```

Destruct the allocator object.



### 5.2 成员函数

| 函数名                 | 作用                                                         |
| ---------------------- | ------------------------------------------------------------ |
| `allocator<T> a`       | 定义一个名为 `a` 的 `allocator`对象，它可以为类型为`T`的对象分配内存。 |
| `a.allocate(n)`        | 分配一段原始的，未构造的内存，可保存`n`个类型为`T`的对象。   |
| `a.deallocate(p, n) `  | 释放从`T*`指针`p`中地址开始的内存，这块内存中保存了`n`个类型为`T`的对象。`p`必须时一个先前由`allocate（）`函数返回的指针，且`n`必须是`p`创建时所要求的大小。在调用`deallocate`之前，用户必须对每个在这块内存中创建的对象调用`destroy`。 |
| `a.construct(p, args)` | `p` 必须是一个类型为`T`的指针，指向一块原始内存：`args` 被传递给类型为`T`的构造函数，用来在`p`指向的内存中构造一个对象。 |
| `a.destroy(p)`         | `p` 为`T*` 类型的指针，此算法对 `p` 指向的对象执行析构函数。 |



```c++
// 使用 allocate 来优化内存分配和释放
#include <iostream>
#include <memory>
#include <string>

void main()
{
	std::allocator<std::string> alloc;
	int n = 100;  // 大小
	std::string* const p = alloc.allocate(n);

	std::string* q = p; // q指向最后构造元素之后的位置

	alloc.construct(q++, 10, 'c');  // *q 为 cccccccccc
	alloc.construct(q++);           // *q 为空字符串
	alloc.construct(q++, "hi");     // *q 为 hi

	size_t str_num = q - p;
	std::cout << "construct string number : " << str_num << std::endl;  // 3

	std::cout << "First contructed string : "    << *p << std::endl;
	std::cout << "Acess uninitialized memory : " << *q << std::endl;  // 访问未初始化的内存，有可能发生灾难性的后果

	// 由 contruct 创建的对象，必须用 destroy 来析构
	while (q != p) alloc.destroy(--q);

	// 当所有元素被销毁后，我们可以用 deallocate 来释放内存
	alloc.deallocate(p, n);
}
```



## 6 未初始化的内存

### 6.1 拷贝和填充未初始化内存的算法

| 函数                                           | 作用                                                         |
| ---------------------------------------------- | ------------------------------------------------------------ |
| `uninitialized_copy(begin, end, destination)`  | 将迭代器`begin`和`end`范围中的元素拷贝到迭代器`destination`所指定的未初始化的原始内存中。`destination` 指向的内存必须足够大，能容纳输入序列中元素的拷贝。 |
| `uninitialized_copy_n(begin,  n, destination)` | 从迭代器`begin` 指向的元素开始，拷贝`n`个元素到`destination`开始的内存中 |
| `uninitialized_fill(begin, end, value)`        | 在迭代器`begin`和`end`指定的原始内存范围中创建对象，对象的值均为`value`的拷贝 |
| `uninitialized_fill_n(begin, n, value)`        | 从迭代器`begin`指向的内存地址开始创建`n`个对象。`begin`必须指向足够大的未初始化的原始内存，能够容纳给定数量的对象。 |



#### 6.1.1 std::uninitialized_copy

```c++
template<class InputIterator, class ForwardIterator>
ForwardIterator unintialized_copy(InputIterator _First, InputIterator _Last, ForwardIterator _Dest);
```

作用： 将 `[_First, _Last)` 区间中的元素以构造的形式在 `_Dest` 为起始位置的内存中初始化。

返回值: 若 `[_First, _Last)` 有 `n` 个元素，则返回值等于 `_Dest + n`。

```c++
// uninitialized demo
#include <iostream>
#include <utility>  // std::size()
#include <memory>   // std::allocator, std::uninitialized_copy

void main()
{
    const char* v[] = { "This", "is", "an", "example" };
    auto v_size = std::size(v);
    
    std::allocator<std::string> str_alloc;
    const int alloc_num = 10;
    std::string* sptr = str_alloc.allocate(alloc_num);

    std::uninitialized_copy(v, v + v_size, sptr);
    
    // 输出字符串
    for (int i = 0; i < v_size; i++) std::cout << *(sptr + i) << std::endl;

    // 将已赋值的对象执行析构
    auto q = sptr + v_size;
    while (q != sptr) str_alloc.destroy(--q);

    // 当所有元素被销毁后，我们可以用 deallocate 来释放内存
    str_alloc.deallocate(sptr, alloc_num);
}
```



#### 6.1.2 std::uninitialized_copy_n

```c++
template<class InputIterator, class Size, class ForwardIterator>
ForwardIterator uninitialized_copy_n(InputIterator _First, Size _N, ForwardIterator _Dest);
```

作用：将以`_First`开头的`_N`个元素，在以`_Dest`为起始位置的内存中构造初始化。

返回值： `_Dest + _N`

```c++
// uninitialized demo
#include <iostream>
#include <utility>  // std::size()
#include <memory>   // std::allocator, std::uninitialized_copy

void main()
{
    const char* v[] = { "This", "is", "an", "example" };
    auto v_size = std::size(v);

    std::allocator<std::string> str_alloc;
    const int alloc_num = 10;
    std::string* sptr = str_alloc.allocate(alloc_num);

    std::uninitialized_copy_n(v, v_size, sptr);

    // 输出字符串
    for (int i = 0; i < v_size; i++) std::cout << *(sptr + i) << std::endl;

    // 将已赋值的对象执行析构
    auto q = sptr + v_size;
    while (q != sptr) str_alloc.destroy(--q);

    // 当所有元素被销毁后，我们可以用 deallocate 来释放内存
    str_alloc.deallocate(sptr, alloc_num);
}
```



#### 6.1.3 std::uninitialized_fill

```c++
template<class ForwardIterator, class T>
void uninitialized_fill(ForwardIterator _First, ForwardIterator _Last, const T& val);
```

作用：将`[First, last)` 中的内存空间用`val` 去构造初始化。



```c++
#include <iostream>
#include <memory>  // std::allocator, std::uninitialized_copy

void main()
{
    std::allocator<std::string> str_alloc;
    const int alloc_num = 10;
    std::string* sptr = str_alloc.allocate(alloc_num);
    std::uninitialized_fill(sptr, sptr+ alloc_num, "Hi");

    // 输出字符串
    for (int i = 0; i < alloc_num; i++) std::cout << *(sptr + i) << std::endl;

    // 将已赋值的对象执行析构
    auto q = sptr + alloc_num;
    while (q != sptr) str_alloc.destroy(--q);

    // 当所有元素被销毁后，我们可以用 deallocate 来释放内存
    str_alloc.deallocate(sptr, alloc_num);
}
```



## 7 其他

## 7.1 <algorithm> 库中的初始化算法

#### 7.1.1 std::copy

```c++
template <class _InIt, class _OutIt>
_OutIt copy(_InIt _First, _InIt _Last, _OutIt _Dest) { // copy [_First, _Last) to [_Dest, ...)
	while(_First != _Last)
    {
        *_Dest = *_First;
        _First++;
        _Dest++;
    }
    return _Dest;
}
```

作用： 将 `[_First, _Last)` 区间中的元素拷贝到以 `_Dest` 为起始位置的内存中。

返回值: 若 `[_First, _Last)` 有 `n` 个元素，则返回值等于 `_Dest + n`。

```c++
// std::copy
#include <iostream>     // std::cout
#include <algorithm>    // std::copy
#include <vector>       // std::vector

void main() {
    int myints[] = { 10,20,30,40,50,66,70 };
    std::vector<int> myvector(7);

    auto ret = std::copy(myints, myints + 7, myvector.begin());
    std::cout << *(myvector.data() + 6) << std::endl;  // 70
    std::cout << *(--ret) << std::endl;                // 70

    std::cout << "myvector contains:";
    for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
        std::cout << ' ' << *it;

    std::cout << '\n';
}
```



#### 7.1.2 std::copy_n

```c++
template<class InputIterator, class Size, class OutputIterator>
OutputIterator copy_n(InputIterator _First, Size _N, OutputIterator _Dest)
{
    while(_N > 0)
    {
        *_Dest = *_First;
        _Dest++;
        _First++;
        _N--;
    }
    return _Dest;
}
```

作用： 将以 `_First` 开头的`_N`个元素拷贝到以 `_Dest` 为起始位置的内存中。

返回值: `_Dest + n`

```c++
// std::copy_n
#include <iostream>     // std::cout
#include <algorithm>    // std::copy
#include <vector>       // std::vector

void main() 
{
    int myints[] = { 10,20,30,40,50,66,70 };
    std::vector<int> myvector(7);

    auto ret = std::copy_n(myints, 7, myvector.begin());
    std::cout << *(myvector.data() + 6) << std::endl;  // 70
    std::cout << *(--ret) << std::endl;                // 70

    std::cout << "myvector contains:";
    for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
        std::cout << ' ' << *it;

    std::cout << '\n';
}
```



#### 7.1.3 std::fill

```c++
template<class ForwardIterator, class T>
void fill(ForwardIterator _First, ForwardIterator _Last, cont T& val)
{
    while(_First != _Last)
    {
        *_First = val;
        _First++;
    }
}
```

作用：将`[_First, last)` 中指定的内存区间，用 `val` 去填充。