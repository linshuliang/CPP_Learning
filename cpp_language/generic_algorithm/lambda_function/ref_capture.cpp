#include <iostream>

void main()
{
	size_t v1 = 28;
	auto f = [&v1] { return v1; };

	v1 = 1;
	auto j = f();
	std::cout << j << std::endl;
}