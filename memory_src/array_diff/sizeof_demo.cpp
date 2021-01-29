#include <iostream>

void main()
{
	char a[] = "world";
	std::cout << sizeof(a) << std::endl;  // 6

	char* p = "world";
	std::cout << sizeof(p) << std::endl;  // 8

	system("pause");
}