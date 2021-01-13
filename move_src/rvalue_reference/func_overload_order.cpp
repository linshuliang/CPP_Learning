#include <iostream>
#include <memory>
#include <utility>

class Data
{
public:
	Data(int i) : data_(i) {}
	void Display() const { std::cout << "[Data::Display] " << data_ << std::endl; }  // 常量对象只能调用 const 函数

private:
	int data_;
};

void func(const Data& d)
{
	std::cout << "Call const-reference function" << std::endl;
	d.Display();
}

void func(Data&& d)
{
	std::cout << "Call right-reference function" << std::endl;
	d.Display();
}

void main()
{
	func(Data(10));
}

/* 终端输出
Call right-reference function
[Data::Display] 10
*/