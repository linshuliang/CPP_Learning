## 1. RAII是什么

RAII是C++里关于资源（包括内存，socket，锁，句柄等）的最重要的概念之一。RAII在字面意思上即**Resource Acquisition is Initialization**（资源获取即初始化）。这是一个十分糟糕的名字，RAII只表达这个概念一半的意思。完整的说法应当是“资源获取即初始化，**且资源回收即释放**”。在C++里，由于资源管理完全掌握在程序员手中，程序员的疏忽很容易造成资源的泄漏和重复释放等问题。使用RAII可以避免大部分资源问题。

C++是一门面向对象的语言，RAII利用面向对象的特性进行资源管理。常见的做法是，将资源封装到一个类中，在它的**构造函数**中**获取资源**，并在它的**析构函数**中**释放资源**。以内存资源为例，假设利用Buffer类对内存进行管理。

```c++
class Buffer 
{ 
public:    
 	explicit Buffer(size_t size) 
    {
        mem_ = malloc(size);
    }
 	
 	~Buffer() 
    {
        if (!mem_)
        { 
            free(mem_); 
        }    
    }
 
 private:    
    void *mem_; 
};
```

那么 `Buffer` 实例就会在离开作用域时，自动将内存释放，而不需要程序员手动对内存进行额外处理。

## 2. 异常安全

`RAII`可以保证异常安全。仍然以内存为例，比较

```c++
float *array = new float[1000]; // do something... Oops, throws exception delete[] array;
```

和

```c++
std::vector<float> array(1000); // do something... Oops, throws exception
```

若采用第一种方案，那么在异常抛出时，array指向的内存将永远得不到释放；

而第二种方案可以安全地将局部变量array析构，同时释放内部的资源。

## 3. 代码清晰度

使用RAII可以提高减少错误处理代码，从而提高整体的可读性。考虑

```c++
float *array = new float[1000]; 
bool ok = process_foo(array); 
if(!ok) 
{ 
    delete[] array; return; 
} 

ok = process_bar(array); 
if(!ok) 
{ 
    delete[] array; return; 
} 

ok = process_baz(array); 
if(!ok) 
{ 
    delete[] array; return; 
}
delete[] array;
```

如果使用RAII，则可以省去所有错误时释放内存的代码，使代码更加聚焦于业务本身。

解决方法1：

```
std::vector<float> array(1000, 0);
```

解决方法2：

```C++
#include <iostream>

template<typename T>
class Array
{
public:
    explicit Array(size_t arr_size)
    {
        _arr_data = new T[arr_size];
    }

    void assign(size_t i, T value)
    {
        _arr_data[i] = value;
    }

    T operator [] (size_t i)
    {
        return _arr_data[i];
    }

    ~Array()
    {
        if (_arr_data != nullptr)
            delete[] _arr_data;
    }

private:
    T* _arr_data;
};

int main()
{
    int arr_size = 100;
    Array<float> arr(arr_size);
    for (int i = 0; i < arr_size; i++)
    {
        arr.assign(i, std::pow(i, 2));
    }

    for (int i = 0; i < arr_size; i++)
        std::cout << arr[i] << std::endl;

	system("pause");
	return 0;
}
```



## 4. C++标准库中的RAII

C++标准库中，也有不少利用RAII对资源进行管理的例子。

**智能指针**（如`std::unique_ptr`, `std::shared_ptr`），它们的构造函数以指针为参数，并在适当的时候“智能”地将资源释放。

**std::lock_guard** 在构造时上锁，并在析构时解锁，常用于线程安全。

**STL容器** 可以作为安全的内存管理类，虽然它们的作用不止于此。

## 5. 实践中的建议

**Prefer STL Container** 当需要一片连续内存时，尽量使用STL容器，例如std::vector，而不是手动去malloc或new一个动态数组。当性能要求比较高时，使用智能指针。

```
std::unique_ptr<char[]> p(new char[1000000]);
```

**避免new和malloc ** 尽量在上层业务中使用new和malloc，如果必须使用，利用RAII封装它们。

**避免使用裸指针** 考虑使用智能指针。

## 6. 扩展与延伸

### 6.1 std::vector v.s. std::unique_ptr

对于内存的处理上，std::vector和智能指针的差异在于，std::vector会将内存初始化为0，而智能指针不会对内存进行处理。因此在对性能要求比较高的程序中，考虑使用智能指针，而不是std::vector。在Intel i5处理器上分配10MB内存，使用std::vector和智能指针的性能可以相差1000倍以上。

### 6.2 Ownership

资源的所有权（ownership）是资源管理的核心概念。即使是使用智能指针，也会涉及到有关于所有权的问题。参考

[F.26: Use a unique_ptr to transfer ownership where a pointer is needed](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#f26-use-a-unique_ptrt-to-transfer-ownership-where-a-pointer-is-needed)

[F.27: Use a shared_ptr to share ownership](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#f27-use-a-shared_ptrt-to-share-ownership)

[R.20: Use unique_ptr or shared_ptr to represent ownership](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rr-owner)

[R.21: Prefer unique_ptr over shared_ptr unless you need to share ownership](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rr-unique)

[CP.32: To share ownership between unrelated threads use shared_ptr](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#cp32-to-share-ownership-between-unrelated-threads-use-shared_ptr)

### 6.3 RAII的变种

利用RAII类似的原理，可以做更多的事情。例如简单的计时器，在构造时开始计时，在析构时结束。

```c++
#include <chrono>

class AutoTimer
{ 
public: 	
    AutoTimer() : beg_(std::chrono::high_resolution_clock::now()) {} 	 	
    ~AutoTimer()  	
    { 		
        auto end = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - beg_);
        std::cout << dur.count() << " musec\n";
    }
private: 	
    std::chrono::time_point<std::chrono::high_resolution_clock> beg_;
}; 

void main() 
{ 
    { 	
        AutoTimer timer; 	
        foo(); 
    } 	
    
    { 	
        AutoTimer timer; 	
        bar(); 
    }
}
```

除此之外，也可以做类的实例数统计，内存泄漏检查等等。

