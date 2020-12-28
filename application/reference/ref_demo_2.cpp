#include <iostream>

void swapRef(int& x, int& y);
void swapPtr(int* x, int* y);

int main()
{
    int i = 12;
    int j = 25;

    swapRef(i, j);
    swapPtr(&i, &j);

    return 0;
}

void swapRef(int& x, int& y)
{
    std::cout << "Call swap with Ref" << std::endl;

    int t;
    t = x;
    x = y;
    y = t;
}

void swapPtr(int* x, int* y)
{
    std::cout << "Call swap with Ptr" << std::endl;

    int t;
    t = *x;
    *x = *y;
    *y = t;
}