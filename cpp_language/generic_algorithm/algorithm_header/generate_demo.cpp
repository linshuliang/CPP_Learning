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