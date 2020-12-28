#include <iostream>

double vals[] = { 10.1, 12.6, 33.1, 24.1, 50.0 };

double& setValues(int i)
{
    return vals[i];   // 返回第 i 个元素的引用
}

int main()
{
    int arr_size = sizeof(vals) / sizeof(double);

    std::cout << "改变前的值" << std::endl;
    for (int i = 0; i < arr_size; i++)
    {
        std::cout << "vals[" << i << "] = ";
        std::cout << vals[i] << std::endl;
    }

    setValues(1) = 20.23; // 改变第 2 个元素
    setValues(3) = 70.8;  // 改变第 4 个元素

    std::cout << "\n改变后的值" << std::endl;
    for (int i = 0; i < arr_size; i++)
    {
        std::cout << "vals[" << i << "] = ";
        std::cout << vals[i] << std::endl;
    }
    return 0;
}