#include <algorithm>
#include <iostream>
#include <vector>

void main()
{
	std::vector<int> mv = { 10, 30, 5, 15, 20 };
	std::make_heap(mv.begin(), mv.end());

	for (auto var : mv) std::cout << var << "  ";
	std::cout << std::endl;
}
