#include <iostream>
#include <memory>
#include <utility>

class Data
{
public:
	Data(int i) : data_(i) {}
	void Print() { std::cout << "[Data::Print] " << data_ << std::endl; }
	void Display() const { std::cout << "[Data::Display] " << data_ << std::endl; }  // 常量对象只能调用 const 函数
	// 如果 const 函数不小心修改了类成员或者调用了非 const 函数，编译器会找出这个错误。

private:
	int data_;
};

void func(const Data& d)
{
	// d.Print();  // ERROR : 对象含有与成员函数不兼容的限定符，对象类型是 const Data
	d.Display();  // d 是 const 类型变量，它只能调用 const 函数
	Data a = d;
	a.Print();
}

void main()
{
	Data d1(10);
	func(d1);  // d1 是左值，const引用能接受左值初始化
	func(Data{ 15 });  // Data { 15 } 是右值， const引用能接受右值初始化
}