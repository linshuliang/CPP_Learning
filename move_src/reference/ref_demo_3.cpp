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