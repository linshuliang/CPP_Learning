#include <iostream>
#include <memory>
#include <vector>

std::unique_ptr<int> func1(int num = 10)
{
	std::unique_ptr<int> ret = std::make_unique<int>(num);
	return ret;  // C++会把即将离开作用域的非引用类型的返回值当成右值，进而调用移动构造函数
}

std::unique_ptr<int> func2(std::unique_ptr<int>&& val)
{
	return std::move(val);  // 完美转发
}

void main()
{
	auto up = func1(18);
	std::cout << "Return value of func1: " << *up << std::endl;

	auto up2 = func2(std::move(up));
	std::cout << "Return value of func2: " << *up2 << std::endl;
}