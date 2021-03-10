#include <iostream>

class Base
{
public:
	static Base* newAnObject();
	static Base makeAnObject();

private:
	Base();
	Base(const Base&);
};

Base::Base()
{
	std::cout << "Default Constructor" << std::endl;
}

Base::Base(const Base&)
{
	std::cout << "Copy Constructor" << std::endl;
}

Base* Base::newAnObject()
{
	return new Base();
}

Base Base::makeAnObject()
{
	return Base();
}

void main()
{
	// Base b;  // 无法访问
	Base* bp = Base::newAnObject();
	delete bp;

	Base::makeAnObject();  // 正确
	// Base bc = Base::makeAnObject();  // 错误，拷贝构造函数为 private
}