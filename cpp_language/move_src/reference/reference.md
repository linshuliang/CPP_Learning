# 引用

引用(`reference`) 像指针，但不是指针。引用主要有 3 种用法：

- 单独使用
- 作参数使用
- 作返回值使用



从功能上来说，引用型变量又可以看做是被引用变量的 “别名”，这两个变量只是名称不同，变量的地址是同一个（共用体中的元素也是一样）。

声明引用时，只是将别名绑定到被引用变量，没有分配新的内存空间。

“引用” 的好处主要是可以“逆向引用”。



定义独立引用时，需要注意以下规则：

- 引用型变量在定义时必须初始化。
- 被引用的对象必须已经分配了空间，即不能为空，或空指针。
- 被引用的对象不能是地址，也不能是指针变量。
- 非常量引用的初始值必须为左值。



### 引用数组 v.s. 数组的引用 

* 不允许使用引用数组。例如`int& ref[3]` 是错误的。**声明引用数组没有办法分配空间**。
* 数组的引用。可以建立数组的引用，例如 `int arr[3] = {1, 2, 5}; int (&arr_ref)[3] = arr; ` arr_ref 是 arr 的一个别名。 

```c++
#include <iostream>
#include <utility>

void main()
{
	int arr[] = { 1, 2, 5 };
	const auto arr_size = std::size(arr);
	// int& int_ref = arr;       // ERROR : int_ref 的类型是 int&, arr 的类型是 int[3]，类型不匹配
	// int& ref[3] = {3, 8, 6};  // ERROR : 不允许使用引用的数组

	int (&ref_arr)[arr_size] = arr;  

	for (int i = 0; i < arr_size; i++)
		std::cout << arr[i] << std::endl;
}
```



## 示例

### 变量引用

```c++
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

    // int x[] = {12,15,20};
    // int &y = x; // 错误: 数组、指针不能被引用
    // int x1;
    // int &y1;    // 错误: 引用时必须初始化
    // y1 = x1;
}
```



### 函数的参数引用

```c++
#include <iostream>

void swapRef(int& x, int& y);

void main()
{
    int i = 12;
    int j = 25;
    swapRef(i, j);
    std::cout << i << ", " << j << std::endl;  // 25, 12
}

void swapRef(int& x, int& y)
{
    std::cout << "Call swap with Ref" << std::endl;

    int t;
    t = x;
    x = y;
    y = t;
}
```



### 对象引用作参数

```c++
#include <iostream>

class Person 
{
private:
    int who;

public:
    Person() = default;

    // 构造函数
    Person(int n) 
    {
        who = n;
        std::cout << "构造函数 : " << who << std::endl;
    }

    ~Person()
    {
        std::cout << "析构函数 : " << who << std::endl;
    }

    // 拷贝构造函数，禁止隐式的类型转换
    // explict 构造函数不是转换构造函数，不被复制初始化考虑
    explicit Person(const Person& p)
    {
        who = p.who;
        std::cout << "const 拷贝构造函数 : " << who << std::endl;
    }

    Person& operator=(const Person& p)
    {
        who = p.who;
        std::cout << "拷贝赋值函数 : " << who << std::endl;
        return *this;
    }

    int id() 
    {
        return who;
    }
};

void f1(Person o) 
{    
    // 普通变量方式传递参数
    std::cout << "外部函数 f1 : " << o.id() << std::endl;
}

void f2(Person* o) 
{    
    // 指针方式传递参数
    std::cout << "外部函数 f2 : " << o->id() << std::endl;
}

void f3(Person& o) 
{    
    // 引用方式传递参数
    std::cout << "外部函数 f3 : " << o.id() << std::endl;
}

void main()
{
    Person x1(1);
    // f1(x1);  // explict 构造函数不是转换构造函数，不被复制初始化考虑
    std::cout << "-------" << std::endl;

    Person x2(2);
    f2(&x2);
    std::cout << "-------" << std::endl;

    Person x3(3);
    f3(x3);
    std::cout << "-------" << std::endl;

    Person x4;
    x4 = x3;
    std::cout << "-------" << std::endl;
    
	Person x5(x1);
    std::cout << "-------" << std::endl;
}

/*
构造函数 : 1
-------
构造函数 : 2
外部函数 f2 : 2
-------
构造函数 : 3
外部函数 f3 : 3
-------
拷贝赋值函数 : 3
-------
const 拷贝构造函数 : 1
-------
析构函数 : 3
析构函数 : 3
析构函数 : 2
析构函数 : 1
*/
```

当函数参数为类对象时，函数首先将参数复制一份副本（调用类的拷贝复制函数），在函数内使用的是副本。

当函数参数为类对象的引用或者指针时，函数内使用的就是类对象本身。



### 把引用作为返回值

C++ 函数可以返回一个引用。当函数返回一个引用时，实际上返回的是一个指向返回值的隐式指针，这样，函数就可以放在赋值语句的左边。

```c++
#include <iostream>

double vals[] = { 10.1, 12.6, 33.1, 24.1, 50.0 };

double& setValues(int i)
{
    return vals[i];   // 返回第 i 个元素的引用
}

void main()
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
}
```

当返回一个引用时，要注意被引用的对象不能超出作用域，返回一个对局部变量的引用是不合法的。



### 引用和指针的区别

C++primer 中对象的定义：对象是指一块能存储数据并具有某种类型的内存空间。
一个对象 a，它有值和地址&a，运行程序时，计算机会为该对象分配存储空间，来存储该对象的值，我们通过该对象的地址，来访问存储空间中的值。

```c++
int a = 10;
int * const p = &a;
int &r = a;           // 引用本质上等同于【常量指针】，也即不能修改其所指向的对象
```



虽然引用本质上等同于常量指针，但引用不等同于常量指针，从变量大小即可看出。

```c++
char c = 'a';
char& cr = c;
char* const p = &c;
std::cout << sizeof(c) << std::endl;   // 1
std::cout << sizeof(cr) << std::endl;  // 1
std::cout << sizeof(p) << std::endl;   // 8
```



**引用的一个优点**:

​	引用一定不为空，因此相对于指针，它不用检查它所指向的对象是否为空，这增加了效率。



