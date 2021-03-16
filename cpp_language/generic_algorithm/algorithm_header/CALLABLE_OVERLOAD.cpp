#include <iostream>

class Distance
{
private:
	int x;
	int y;

public:
	Distance();
	Distance(int, int);
	Distance operator()(int a, int b, int c);  // 重载函数调用运算符
	void displayDistance();
};

Distance::Distance()
{
	x = 0; 
	y = 0;
}

Distance::Distance(int i, int j)
{
	x = i;
	y = j;
}

Distance Distance::operator()(int a, int b, int c)
{
	Distance d;
	d.x = a + c + 10;
	d.y = a + b + 100;
	return d;
}

void Distance::displayDistance()
{
	std::cout << "X: " << x << ", Y: " << y << std::endl;
}

void main()
{
	Distance D1(10, 20);
	std::cout << "Distance 1 : ";
	D1.displayDistance();

	// 函数运算符重载
	Distance D2 = D1(10, 20, 30);
	std::cout << "Distance 2 : ";
	D2.displayDistance();
}