## C++ 函数指针

函数存放在内存的代码区域内，它们同样有地址。函数的地址就是函数的名字，这一点跟数组一样，数组的名字就是数组的起始地址。



## 函数指针定义方式

```c++
data_types (*func_pointer)(data_types arg1, data_types arg2, ..., data_types argn);
```

普通函数指针实际上保存的是函数体的开始地址，因此也称为"代码指针"，以区别于 C/C++ 最常用的数据指针。



例如：

```c++
int (*fp)(int a);
```

`fp` 是一个函数指针，函数的参数是一个整数，函数的返回值是 `int` 类型。



**Demo_1**

```c++
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
```



## `typedef` 可以简化函数指针的定义

`typedef` 定义函数指针：

```c++
typedef data_types (*func_pointer)(data_types arg1, data_types arg2, ..., data_types argn);
```

与函数指针的定义不同的是：需要在最前面加关键字 `typedef`。



```c++
#include <iostream>

int test(int a)
{
	std::cout << "Call test()" << std::endl;
	return a * 10;
}

typedef int(*fp)(int a);  // 定义 fp 为一个函数指针

int main()
{
	fp f = test;
	std::cout << f(1) << std::endl;
	return 0;
}
```



## 函数指针同样可以作为参数传递给函数

```c++
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
```

输出为：

```
Call test2(int (*fp)(int), int b)
Call test(int a)
11
Call test3(func_ptr fp)
Call test(int a)
9
```





