#include <iostream>

int test(int a)
{
	std::cout << "Call test()" << std::endl;
	return a * 10;
}

typedef int(*fp)(int a);  // ���� fp Ϊһ������ָ��

int main()
{
	fp f = test;
	std::cout << f(1) << std::endl;
	return 0;
}
