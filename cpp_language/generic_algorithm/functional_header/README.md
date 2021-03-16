

# <functional> 头文件

## 1 基本概念

 ### 1.1 函数对象 (Function objects)

*Function objects* are objects specifically designed to be used with a syntax similar to that of functions. In C++, this is achieved by defining member function `operator()` in their class, like for example:

```c++
struct transform
{
    int operator()(int a)
    {
        return a;
    }
};

int x = transform(0);  // function-like syntax 
```

They are typically used as arguments to functions, such as *predicates* or *comparison functions* passed to standard [algorithms](https://www.cplusplus.com/algorithm).



## 1.2 operator classes

```c++
// Definitions - std::less
template<class _Ty = void>
struct less
{	
	constexpr bool operator()(const _Ty& _Left, const _Ty& _Right) const
	{	// apply operator< to operands
		return (_Left < _Right);
	}
};
```

将 `std::less` 用于 `std::sort`

```c++
// Demo - std::less
#include <iostream>     // std::cout
#include <functional>   // std::less, std::greater
#include <algorithm>    // std::sort

void main() 
{
	int foo[] = { 10,20,5,15,25 };
	int bar[] = { 15,10,20 };
	std::sort(foo, foo + 5, std::less<int>());     // 5 10 15 20 25
	std::sort(bar, bar + 3, std::greater<int>());  // 20 15 10

	for (auto &x : foo) std::cout << x << "  ";
	std::cout << std::endl;
	for (auto &y : bar) std::cout << y << "  ";
	std::cout << std::endl;
	system("pause");
}
```



