// vector::shrink_to_fit
#include <iostream>
#include <vector>

void main()
{
	std::vector<int> myvector(100, 2);
	std::cout << "1. capacity of myvector: " << myvector.capacity() << '\n';  // 100
	std::cout << "1. size of myvector: " << myvector.size() << '\n';  // 100

	myvector.resize(10);
	std::cout << "2. capacity of myvector: " << myvector.capacity() << '\n';  // 100
	std::cout << "2. size of myvector: " << myvector.size() << '\n';  // 10

	myvector.shrink_to_fit();
	std::cout << "3. capacity of myvector: " << myvector.capacity() << '\n';  // 10
	std::cout << "3. size of myvector: " << myvector.size() << '\n';  // 10
}