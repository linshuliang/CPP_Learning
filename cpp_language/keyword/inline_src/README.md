## C++ 中的 inline 用法

## 1 引入 inline 关键字的原因

在 c/c++ 中，为了解决一些频繁调用的小函数大量消耗栈空间（栈内存）的问题，特别的引入了 **inline** 修饰符，表示内联函数。

栈空间就是指放置程序的局部数据（也就是函数内数据）的内存空间。

在系统下，栈空间是有限的，假如频繁大量的使用就会造成因栈空间不足而导致程序出错的问题，如，函数的死循环递归调用的最终结果就是导致栈内存空间枯竭。



```c++
// inline demo
#include <iostream>

inline const char *num_check(int v) 
{ 
	return (v % 2 > 0) ? "奇" : "偶"; 
} 

void main() 
{ 
	for (int i = 0; i < 100; i++) 
		std::cout << i << " " << num_check(i) << std::endl;
	system("pause");
}
```

上面的例子就是标准的内联函数的用法，使用 `inline` 修饰带来的好处我们表面看不出来，其实质在每个 `for` 循环中任何调用 `num_check(i)` 的地方都换成了 `(i%2>0)?"奇":"偶"`，这样就避免了频繁调用函数对栈内存重复开辟所带来的消耗。



### 2 inline 使用限制

`inline` 的使用是有限制的，`inline` 只适用于简单函数，不能包含复杂的控制语句（例如 `while`、`switch`），并且内联函数本身不能是递归函数。



### 3 inline 仅是一个对编译器的建议

`inline` 关键字仅仅是一个对编译器的建议，所以最后能否真正内联，看编译器的意思，它如果认为函数不复杂，能在调用点展开，就会真正内联，并不是有`inline`关键字就会内联，这仅仅是一个建议而已。



### 4 inline 是一种"用于实现的关键字"

关键字 `inline` 必须和函数定义体放在一起才能使函数成为内联，仅将 `inline` 关键字放在函数声明前面不起任何作用。



正确的`inline`：

```c++
void foo();
inline void foo() { do_something; }
```