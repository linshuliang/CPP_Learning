#include <iostream>
#include <string>

// 因为写了析构函数，因此必须显式声明 拷贝构造/拷贝赋值，移动构造/移动赋值，=default 表示让编译器自动生成默认的
class Tracer 
{
private:
    std::string message;

public:
    Tracer(const std::string& m) : message{ m } { std::cerr << "entering " << message << '\n'; }
    ~Tracer() { std::cerr << "exiting " << message << '\n'; }

    Tracer(const Tracer&) = default;
    Tracer& operator=(const Tracer&) = default;
    Tracer(Tracer&&) = default;
    Tracer& operator=(Tracer&&) = default;
};

// 写出复制和移动操作的主体是冗长，乏味且容易出错的, 编译器会做得更好。
class BadTracer 
{
private:
    std::string message;
public:
    BadTracer(const std::string& m) : message{ m } { std::cerr << "entering " << message << '\n'; }
    ~BadTracer() { std::cerr << "exiting " << message << '\n'; }

    BadTracer(const BadTracer& a) : message{ a.message } {}
    BadTracer& operator=(const BadTracer& a) { message = a.message; return *this; }
    BadTracer(BadTracer&& a) : message(a.message) {}
    BadTracer& operator=(BadTracer&& a) { message = a.message; return *this; }
};

void main()
{
    Tracer gt("good tracer");
    BadTracer bt("bad tracer");
}