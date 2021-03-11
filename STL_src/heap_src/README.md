# C++ 堆

 ## 1 数据结构中的堆

### 1.1 完全二叉树

**满二叉树** ：一棵深度为`k`且有`pow(2,k) - 1`个结点的二叉树称为满二叉树。

**完全二叉树** ：一棵深度为`k`的有`n`个结点的二叉树，对树中的结点按从上至下、从左到右的顺序进行编号，如果编号为`i(1≤i≤n)`的结点与满二叉树中编号为`i`的结点在二叉树中的位置相同，则这棵二叉树称为完全二叉树。



### 1.2 堆的定义

堆：堆是一个完全二叉树，每个节点与其子节点位置相对，堆可分为如下两种：

* 大顶堆 ：父节点的值大于或等于子节点
* 小顶堆 ：父节点的值小于或等于子节点



## 2 C++ 中与堆相关的内置函数

| 函数                   | 作用                                                         |
| ---------------------- | ------------------------------------------------------------ |
| `make_heap`            | 创建堆                                                       |
| `push_heap`            | 在容器的末尾新增一个元素，然后可调用 push_heap 来重排，使得新增元素后的容器仍为堆 |
| `pop_heap`             | 将堆顶元素移至容器的末尾，然后重排 [first, last-1) 使得其为堆 |
| `is_heap(first, last)` | 判断 `[first, last)` 是否为一个堆                            |
| `sort_heap`            | 作用等同于 make_heap                                         |

注意，C++ 中有关堆的内置函数，并不会创建出 [堆] 容器，而是组织容器元素的一种特殊方式。



### 2.1 make_heap

```c++
// 创建大顶堆，比较函数为 std::less<element_type>()
template<class RandomAcessIterator>
void make_heap(RandomAccessIterator first, RandomAccessIterator last);

// 自定义比较函数， std::less<element_type>() 为大顶堆， std::greater<element_type>() 为小顶堆
// 如果 element_type 不是内置数据类型，则需要自定义 ·函数调用运算符· 或者 ·lambda函数·
template<class RandomAcessIterator, class Compare>
void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);    
```

作用 ： Rearranges the elements in the range `[first,last)` in such a way that they form a *heap*.

示例 : 

```c++
// Demo - std::make_heap 
#include <algorithm>  // std::make_heap
#include <iostream>
#include <vector>
#include <cmath>      // pow

struct Circle
{
	float x_;
	float y_;
	
	Circle(float x, float y) : x_(x), y_(y) {}
};

void main()
{
	std::vector<int> mv = { 10, 30, 5, 15, 20 };

	// 大顶堆
	std::make_heap(mv.begin(), mv.end());
	for (auto var : mv) std::cout << var << "  ";
	std::cout << std::endl;

	// 小顶堆
	std::make_heap(mv.begin(), mv.end(), std::greater<int>());
	for (auto var : mv) std::cout << var << "  ";
	std::cout << std::endl;

	// 结构体 -> 大顶堆
	std::vector<Circle> vc = { Circle(1, 2), Circle(2, 3), Circle(0, 1) };
	std::make_heap(vc.begin(), vc.end(), [](const Circle& a, const Circle& b) -> bool {
		if ((pow(a.x_, 2) + pow(a.y_, 2)) < (pow(b.x_, 2) + pow(b.y_, 2)))
			return true;
		else
			return false;
	});
	for (auto c : vc)
	{
		std::cout << c.x_ << "  " << c.y_ << std::endl;
	}
}
```



### 2.2 push_heap

```c++
// 向大顶堆中新增元素
template<class RandomAccessIterator>
void push_heap(RandomAccessIterator first, RandomAccessIterator last);

// 自定义比较函数， std::less<element_type>() 为大顶堆， std::greater<element_type>() 为小顶堆
// 如果 element_type 不是内置数据类型，则需要自定义 ·函数调用运算符· 或者 ·lambda函数·
template<class RandomAccessIterator, class Compare>
void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);
```

作用：push element into heap range.  假定 `[first, last-1)` 已经是一个堆了。当往容器中的`last-1`位置插入一个元素后，可调用 `push_heap` 来重排，使得`[first, last)` 是一个堆。 

**注意：** `push_heap` 的参数 `comp` 需跟 `make_heap` 中的 `comp` 一模一样。

示例：

```c++
// Demo - std::push_heap
#include <algorithm>  // std::make_heap, push_heap
#include <iostream>
#include <vector>

template<class T>
void print_vec(const std::vector<T>& mv)
{
	for (auto var : mv) std::cout << var << "  ";
	std::cout << std::endl;
}

void main()
{
	std::vector<int> mv = { 10, 30, 5, 15, 20 };

	std::make_heap(mv.begin(), mv.end(), std::greater<int>());
	print_vec(mv);
	/* 小顶堆
	*        5
	*    15     10
	* 30    20
	*/

	mv.push_back(60);
	std::push_heap(mv.begin(), mv.end(), std::greater<int>());
	print_vec(mv);
	/* 小顶堆
	*              5
	*      15              10
	*  30      20      60
	*/

	// mv.push_back(3);
	// mv.push_back(7);
	// std::push_heap(mv.begin(), mv.end(), std::greater<int>());
	// print_vec(mv);
	/* 往容器末尾插入的元素个数大于1时，再调用push_heap，结果有可能不是堆
	*                5 
	*         7             10
	*     15     20     60       3
	* 30
	*/

	mv.push_back(3);
	mv.push_back(7);
	std::push_heap(mv.begin(), mv.end() - 1, std::greater<int>());
	std::push_heap(mv.begin(), mv.end(), std::greater<int>());
	print_vec(mv);
	/* 往容器末尾插入的元素个数大于1时，调用 push_heap 的次数等于末尾插入的元素个数时，结果才为堆
	*                3
	*         7             5
	*     15     20     60       10
	* 30
	*/

	mv.insert(mv.begin(), 101);
	std::push_heap(mv.begin(), mv.end(), std::greater<int>());
	print_vec(mv);
	// 如果插入元素的位置不是容器的末尾，则结果不为堆
	// 101  3  7  5  15  20  60  10  30
}
```



### 2.3 pop_heap

```c++
template <class RandomAccessIterator>
void pop_heap(RandomAccessIterator first, RandomAccessIterator last);

template <class RandomAccessIterator, class Compare>
void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);
```

**作用**：Pop elements from heap range. 若 `[first, last)` 是一个堆，调用 `pop_heap` 后， `[first, last - 1)` 仍为一个堆。只是原堆顶元素 `*first` 被移到了 `last` 位置。弹出 `last`，则 `[first, last - 1)` 仍为一个堆。

**注意：** `push_heap` 的参数 `comp` 需跟 `make_heap` 中的 `comp` 一模一样。

**示例**：

```c++
// Demo - std::pop_heap
#include <algorithm>  // std::pop_heap
#include <iostream>
#include <vector>

template<class T>
void print_vec(const std::vector<T>& mv)
{
	for (auto var : mv) std::cout << var << "  ";
	std::cout << std::endl;
}

void main()
{
	std::vector<int> mv = { 10, 30, 5, 15, 20 };

	std::make_heap(mv.begin(), mv.end(), std::greater<int>());
	print_vec(mv);
	/* 小顶堆
	*        5
	*    15     10
	* 30    20
	*/

	std::pop_heap(mv.begin(), mv.end(), std::greater<int>());
	mv.pop_back();
	print_vec(mv);
	/* 小顶堆
	*       10
	*    15    20
	* 30    
	*/
}
```



## 参考

* [C++ 堆用法详解](http://c.biancheng.net/view/481.html)
* [完全二叉树](https://baike.baidu.com/item/%E5%AE%8C%E5%85%A8%E4%BA%8C%E5%8F%89%E6%A0%91)
* [push_heap](http://www.cplusplus.com/reference/algorithm/push_heap/)