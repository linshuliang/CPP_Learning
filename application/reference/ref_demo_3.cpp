#include <iostream>

class Person 
{
private:
    int who;

public:
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

    Person(const Person& p)
    {
        who = p.who;
        std::cout << "拷贝构造函数 : " << who << std::endl;
    }

    int id() 
    {
        return who;
    }
};

void f1(Person o) 
{    
    //普通变量方式传递参数
    std::cout << "外部函数 f1 : " << o.id() << std::endl;
}

void f2(Person* o) 
{    
    //指针方式传递参数
    std::cout << "外部函数 f2 : " << o->id() << std::endl;
}

void f3(Person& o) 
{    
    //引用方式传递参数
    std::cout << "外部函数 f3 : " << o.id() << std::endl;
}
int main()
{
    Person x1(1);
    f1(x1);
    std::cout << "-------" << std::endl;

    Person x2(2);
    f2(&x2);
    std::cout << "-------" << std::endl;

    Person x3(3);
    f3(x3);
    std::cout << "-------" << std::endl;

    return 0;
}