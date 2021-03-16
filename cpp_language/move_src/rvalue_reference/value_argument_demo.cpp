#include <iostream>
#include <string>

class Person
{
public:
	Person(std::string name_) : name(name_) { std::cout << "Construct " << name_ << std::endl; }

private:
	std::string name;
};

void main()
{
	Person a("Alice"); // 先调用构造函数 string(const char*)，再调用 Person(std::string) 构造函数。
	std::string b_name = "benz";
	Person b(b_name); // 调用 Person(std::string) 构造函数
}