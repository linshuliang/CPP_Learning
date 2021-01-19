# C++ lambda 表达式

## 1 简介

一个 lambda 表达式是一个可调用的代码单元，它是一种定义匿名函数对象的简便方法。



一个 lambda 表达式具有如下形式：

```c++
[capture_list](parameter_list) -> return_type { function_body }
```

其中：

* `capture_list` ：是一个 `lambda` 表达式所在函数中定义的局部变量的列表（通常为空）
* `return_type`  ： 返回类型
* `parameter_list` : 参数列表
* `function_body` : 函数体 



我们可以忽略参数列表和返回类型，但必须永远包含捕获列表和函数体，例如：

```c++
auto f = [] { return 50; }
```



同时我们可以向 lambda 表达式传递参数，使用捕获列表，例如：

```c++
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

// 去重
void elimDups(std::vector<std::string>& words)
{
	// 按字典
	std::sort(words.begin(), words.end());
	// 重排，使得每个单词只出现一次，返回指向不重复区域之后一个位置的迭代器
	auto end_unique = std::unique(words.begin(), words.end());
	// 删除重复的单词
	words.erase(end_unique, words.end());
}

void main()
{
	std::vector<std::string> strs = { "the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle" };
	elimDups(strs);

	// 按长度排序, 小 -> 大  
	std::stable_sort(strs.begin(), strs.end(), [](const std::string& a, const std::string& b) { return a.size() < b.size(); });

	// 获取一个迭代器，指向第一个满足 size() >= sz 的元素
	const int sz = 3;
	auto wc = std::find_if(strs.begin(), strs.end(), [sz](const std::string& a) { return a.size() > sz; });

	int bigger_count = strs.end() - wc;
	std::cout << "Bigger Count : " << bigger_count << std::endl;

	for (auto it = wc; it != strs.end(); it++)
		std::cout << *it << std::endl;
}
```



## 2 lambda 捕获和返回

类似参数传递，变量的捕获方式可以是值或引用。

### 2.1 值捕获

与传值参数类似，采用值捕获的前提是变量可以拷贝。与参数不同，被捕获的变量在 lambda 创建时拷贝。

```c++
#include <iostream>

void main()
{
	size_t v1 = 28;
	auto f = [v1] {return v1; };  // 被捕获的变量在 lambda 创建时拷贝

	v1 = 0;
	auto j = f();
	std::cout << j << std::endl;  // 28
}
```



### 2.2 引用捕获

一个以引用方式捕获的变量与其他类型的引用的行为类似，当我们在 lambda 表达式内使用此变量时，实际上使用的是引用所绑定的对象。

```c++
#include <iostream>

void main()
{
	size_t v1 = 28;
	auto f = [&v1] {return v1; };

	v1 = 1;
	auto j = f();
	std::cout << j << std::endl;  // 1
}
```



### 2.3 隐式捕获

除了显式列出需要捕获的变量外，还可让编译器根据 lambda 体中的代码来推断我们要使用哪些变量。

为了指示编译器推断捕获列表，应在捕获列表中写一个 `&` 或 `=` ：

`&` 告诉编译器采取 ：引用捕获方式；

`=` 告诉编译器采取 ：值捕获方式；

```c++
#include <iostream>

void main()
{
	size_t v1 = 28;
	auto f = [=] { return v1; };
	auto g = [&] { return v1; };

	v1 = 1;
	auto j = f();
	std::cout << j << std::endl;  // 28

	auto k = g();
	std::cout << k << std::endl;  // 1
}
```



### 2.4 混合使用隐式捕获和显式捕获

可以 混合使用隐式捕获和显式捕获。

```c++
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

void print_strs(std::vector<std::string>& words, std::vector<std::string>::size_type sz, std::ostream& os = std::cout, char c = ' ')
{
	// 除了 c 是赋值捕获（显式）外，其他变量都是引用捕获（隐式）
	std::for_each(words.begin(), words.end(), [&, c](const std::string& s) { os << "[print_strs] " << s << c; });
}

void echo_strs(std::vector<std::string>& words, std::vector<std::string>::size_type sz, std::ostream& os = std::cout, char c = ' ')
{
	// 除了 os 是引用捕获（显式）外，其他变量都是赋值捕获（隐式）
	std::for_each(words.begin(), words.end(), [=, &os](const std::string& s) { os << "[echo_strs] " << s << c; });
}

void main()
{
	std::vector<std::string> strs = { "i", "am", "so", "handsome" };
	print_strs(strs, strs.size());
	echo_strs(strs, strs.size());
}
```



**总结**：

[]：默认不捕获任何变量；

[x]：仅以值捕获x，其它变量不捕获；

[&x]：仅以引用捕获x，其它变量不捕获；

[=]：默认以值捕获所有变量；

[&]：默认以引用捕获所有变量；

[=, &x]：默认以值捕获所有变量，但是x是例外，通过引用捕获；

[&, x]：默认以引用捕获所有变量，但是x是例外，通过值捕获；

[this]：通过引用捕获当前对象（其实是复制指针）；

[*this]：通过传值方式捕获当前对象；



## 3 lambda 表达式的使用场景

### 3.1 封装传递给算法或异步方法的少量代码行

```c++
#include <iostream>
#include <algorithm>  // std::generate
#include <vector> 
#include <cstdlib>  // std::rand

void main()
{
	std::vector<int> my_vec(10);
	std::generate(my_vec.begin(), my_vec.end(), []() -> int { return std::rand() % 100; });

	for (auto it = my_vec.begin(); it != my_vec.end(); it++)
		std::cout << *it << std::endl;
}
```



## 4 补充知识



