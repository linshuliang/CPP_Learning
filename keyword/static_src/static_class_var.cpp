#include <iostream>

class Point 
{
public:	
	Point(int x = 0, int y = 0) : x_(x), y_(y) 
	{
		count++;
	}

	Point(const Point &p) 
	{
		x_ = p.x_;
		y_ = p.y_;
		count++;
	}
	
	~Point() { count--; }
	
	int getX() { return x_; }
	int getY() { return y_; }

	static void showCount() 
	{
		std::cout << "Object Count = " << count << std::endl;
	}

private:	
	int x_, y_;
	static int count;
};

int Point::count = 0;  // 在定义 class Point 时，已在静态存储区分配了内存，初始化时不负责静态存储区的分配，故不能加关键字 static

void main()
{
	Point p1(10, 20);
	Point::showCount();

	Point p2(5, 6);
	Point::showCount();

	system("pause");
}