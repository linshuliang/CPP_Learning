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