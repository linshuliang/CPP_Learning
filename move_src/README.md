# 对象移动





## 右值引用 (rvalue reference)

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



### 左值持久，右值短暂

* 左值有持久的状态；

* 右值要么是字面常量，要么是在表达式求值过程中创建的临时对象；



由于右值引用只能绑定到临时对象，可知：

* 所引用的对象即将被销毁
* 该对象没有其他用户



这两个特性意味着：使用右值引用的代码可以自由地接管所引用对象的资源。







## 参考

[如何评价 C++11 的右值引用（Rvalue reference）特性？](https://www.zhihu.com/question/22111546)











