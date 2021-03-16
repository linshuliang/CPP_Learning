#include <iostream>
using namespace std;

void main()
{
    int a;
    int& b = a;    // 引用型变量是被引用变量的“别名”
    b = 100;       // b 赋值为100，也就是 a 赋值为 100
    cout << a << endl;
    
    cout << &a << endl;  // 变量的地址相同
    cout << &b << endl;  // 变量的地址相同

    // int x[] = {12,15,20} ;
    // int &y = x; // 错误: 数组、指针不能被引用
    // int x1;
    // int &y1;    // 错误: 引用时必须初始化
    // y1 = x1;
}