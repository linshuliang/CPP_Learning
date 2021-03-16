#include <iostream>
#include <memory>

class Foo
{
public:
	Foo() = default;
	Foo(Foo&&) { std::cout << "Move Constructor" << std::endl; };  // move constructor
};

void main()
{
	Foo x;
	// Foo y(x);  // Foo(const Foo&) = delete; 无法引用已经删除的函数
	Foo z(std::move(x));
}

/*  程序输出
Move Constructor
*/