#include <iostream>

void main()
{
	char a[] = "hello";
	a[0] = 'x';
	std::cout << a << std::endl;

	char* p = "world";  // "world" 是常量字符串，常量字符串的内容是不可以修改的
	// p[0] = 'x';  // ERROR : 常量字符串是不可以修改的  
	std::cout << p << std::endl;

	system("pause");
}