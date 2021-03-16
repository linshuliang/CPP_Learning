#include <iostream>

int a;

void main()
{
	static char b[10];
	std::cout << a << std::endl;  // 0
	std::cout << b << std::endl;  // ¿Õ×Ö·û´®
	system("pause");
}