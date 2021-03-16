#include <iostream>
#include <typeinfo>

#define PI 3.14159

int main()
{
    std::cout << "Value of PI :" << PI << std::endl;
    std::cout << "typeid(PI).name() : "  << typeid(PI).name() << std::endl;  // double
 
    return 0;
}
