#include <algorithm>  // std::make_heap
#include <iostream>
#include <vector>
#include <cmath>      // pow

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
