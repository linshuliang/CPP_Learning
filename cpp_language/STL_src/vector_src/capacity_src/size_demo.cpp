// vector::size

//	Syntax:
//		size_type size() const noexcept;
//	
//	Meaning:
//		Returns the number of elements in the vector
//		This is the number of actual objects held in the vector, which is necessarily equal to its storage capacity.

#include <iostream>
#include <vector>

void main()
{
	std::vector<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';  // 0

	for (int i = 0; i < 10; i++) myints.push_back(i);
	std::cout << "1. size: " << myints.size() << '\n';  // 10

	myints.insert(myints.end(), 10, 100);
	std::cout << "2. size: " << myints.size() << '\n';  // 20

	myints.pop_back();
	std::cout << "3. size: " << myints.size() << '\n';  // 19
}