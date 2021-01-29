#include <iostream>

void main()
{
	// extern char a;  // 编译时就会报错 : 无法解析的变量
	// std::cout << a << std::endl;  

	extern char b;
	std::cout << b << std::endl;
	system("pause");
}