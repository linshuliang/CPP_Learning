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
