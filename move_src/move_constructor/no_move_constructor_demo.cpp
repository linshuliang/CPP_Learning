#include <iostream>
#include <memory>

class Foo
{
public:
	Foo() = default;
	Foo(const Foo&) { std::cout << "Copy Constructor" << std::endl; };  // copy constructor
};

void main()
{
	Foo x;
	Foo y(x);
	Foo z(std::move(x));
}

/*  程序输出
Copy Constructor
Copy Constructor
*/