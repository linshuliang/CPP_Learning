#include <iostream>

class Base
{
public:
	virtual void print()
	{
		std::cout << "Call Base::print()" << std::endl;
	}
};

class Test : public Base
{
public:
	// virtual static void func1();	// ERROR : 静态函数不能是虚函数
	const static void func2();

	void print()
	{
		std::cout << "Call Test::print()" << std::endl;
	}
};

const void Test::func2()
{
	std::cout << "Call Test::func2()" << std::endl;
}

void main()
{
	Base* t1 = new Test();
	t1->print();

	std::cout << sizeof(t1) << std::endl;  // 8
}