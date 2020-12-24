#include <iostream>
#include <memory>

void main()
{
	auto myDeleter = [](int* p)
	{
		std::cout << "Call deleter" << std::endl;
		delete p;
	};

	{
		std::shared_ptr<int> var(new int{ 10 }, myDeleter);
		std::cout << "*var = " << *var << std::endl;
	}   // var 离开作用域，执行析构函数

	std::cout << "Main End" << std::endl;
}