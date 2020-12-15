#include <iostream>

int test(int a)
{
    return a * 10;
}

int main(int argc, const char* argv[])
{
    int (*fp)(int a);
    fp = test;
    std::cout << fp(2) << std::endl;
    return 0;
}
