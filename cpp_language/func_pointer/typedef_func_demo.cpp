#include <iostream>

int test(int a)
{
	std::cout << "Call test()" << std::endl;
	return a * 10;
}

typedef int(*fp)(int a);  // 定义 fp 为一个函数指针

int main()
{
	fp f = test;
	std::cout << f(1) << std::endl;
	return 0;
}
