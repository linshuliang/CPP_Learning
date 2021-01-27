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