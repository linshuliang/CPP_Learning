#include <iostream>

int test(int a)
{
    std::cout << "Call test(int a)" << std::endl;
    return a - 1;
}

int test2(int (*fp)(int), int b)
{
    std::cout << "Call test2(int (*fp)(int), int b)" << std::endl;
    int c = fp(10) + b;
    return c;
}

typedef int(*func_ptr)(int);
int test3(func_ptr fp)
{
    std::cout << "Call test3(func_ptr fp)" << std::endl;
    return fp(10);
}

int main(int argc, const char* argv[])
{
    std::cout << test2(test, 2) << std::endl;
    std::cout << test3(test) << std::endl;
    return 0;
}