#include <iostream>

void test()
{
	static int num = 0;
	num++;
	std::cout << num << std::endl;
}

void main()
{
	for (int i = 0; i < 10; i++) test();
	system("pause");
}