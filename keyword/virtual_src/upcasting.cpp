#include <iostream>

class A 
{
private:
	int a;
public:
	void setA(int x) { a = x; }
	int getA() { return a; }
};
class B :public A 
{
private:
	int b;
public:
	void setB(int x) { b = x; }
	int getB() { return b; }
};

void main() 
{
	A a1;
	B b1;
	a1.setA(1);
	b1.setA(2);
	std::cout << "a1 = " << a1.getA() << std::endl;  // 1
	std::cout << "b1 = " << b1.getA() << std::endl;  // 2

	// 把派生类对象赋值给基类对象
	a1 = b1;  // A& A::operator=(const A&);
	std::cout << "a1 = " << a1.getA() << std::endl;  // 2
	std::cout << "b1 = " << b1.getA() << std::endl;  // 2
	
	a1.setA(10);
	std::cout << "a1 = " << a1.getA() << std::endl;  // 10
	std::cout << "b1 = " << b1.getA() << std::endl;  // 2

	// 把派生类对象的地址赋值给基类指针。
	A* ap = &b1;
	std::cout << "*ap = " << ap->getA() << std::endl; // 2

	// 用派生类对象初始化基类对象的引用。
	A& ac = b1;
	std::cout << "ac = " << ac.getA() << std::endl;   // 2

	// b1 = a1;      // ERROR : 无法把基类对象赋值给派生类对象
	// B* bp = &a1;  // ERROR : 无法将基类对象的地址赋值给派生类指针
	// B& bc = a1;   // ERROR : 无法用派生类对象初始化基类对象的引用

	system("pause");
}


