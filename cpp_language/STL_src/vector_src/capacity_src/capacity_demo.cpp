#include <iostream>
#include <vector>

void main()
{
	std::vector<int>::size_type sz;
	std::vector<int> foo;
	sz = foo.capacity();

	std::cout << "Making vector grow" << std::endl;
	for (int i = 0; i < 100; i++)
	{
		foo.push_back(i);
		if (sz != foo.capacity())
		{
			sz = foo.capacity();
			std::cout << "Capacity Changed: " << int(sz) << std::endl;
		}
	}
}