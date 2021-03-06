#include <iostream>
using namespace std;

// ����
class Shape
{
public:
    virtual int getArea() = 0;
    void setWidth(int w) { width = w; }
    void setHeight(int h) { height = h; }

protected:
    int width;
    int height;
};

// ������ 
class Rectangle : public Shape
{
public:
    int getArea() override
    {
        return (width * height);
    }
};

void main()
{
    Rectangle Rect;
    Rect.setWidth(5);
    Rect.setHeight(7);
    cout << "Total area: " << Rect.getArea() << endl;
}