# 类型转换

## 1 隐式转换（implicit conversion）

在下面这些情况中，编译器会自动转换运算对象的类型：

* 在条件判断中，非布尔值转换为布尔类型；
* 初始化过程中，初始值转换为变量的类型；
* 在赋值语句中，右侧运算对象转换为左侧运算对象的类型；
* 如果算数运算的运算对象有多种类型，会自动转换为同一类型，再运算。算数类型之间的隐式转换被设计得尽可能避免精度损失，比如 `int a = 3.6 + 3;` ，编译器会在相加前，将 3 隐式转换为 `3.0` ，然后再与`3.6`相加。然后再由赋值语句进行转换，结果为整数6。

* 如果关系运算的运算对象有多种类型，会自动转换为同一类型，再运算。
* 函数调用时也会发生类型转换。



## 2 C++ 四种类型转换运算符 static_cast,  const_cast, reinterpret_cast, dynamic_cast

隐式类型转换是安全的，显式类型转换是有风险的。C++之所以增加强制类型转换的语法，就是为了强调风险。

但这种强调风险的方式还比较粗放，它并没有表明存在什么风险，风险程度如何。并且，C风格的强制类型转换统一使用`()`，不利于搜索和定位。

为了使潜在风险更加细化，使问题追溯更加方便，使书写格式更加规范，C++对类型转换进行了分类，并新增了4个关键字来支持，分别是：

| 关键字           | 说明                                                         |
| ---------------- | ------------------------------------------------------------ |
| static_cast      | 用于良性转换，一般不会导致意外发生，风险很低。               |
| const_cast       | 用于两种转换：const与非const， volatile 与非 volatile。      |
| reinterpret_cast | 高度危险的类型转换，这种转换仅仅是对二进制位的重新解释，不会借助已有的转换规则对数据进行调整，但可以实现更灵活的C++类型转换。 |
| dynamic_cast     | 本质上，dynamic_cast 只允许向上转型(Up-casting)，因为它只能向上遍历继承链。但派生类对象可以用任何一个基类指针指向它，借助 RTTI，从而可用于类型的向下转型(Down-casting）。 |



这四个关键字的语法格式都是一样的，具体为：

```c++
xxx_cast<newType>(data);
```

其中`newType`是要转换成的新类型，`data`是被转换的数据。



例如，C风格的 `double`转`int`的写法为：

```c++
double scores = 95.5;
int n = (int)scores;
```



C++ 新风格的写法为：

```c++
double scores = 95.5;
int n = static_cast<int>(scores);
```



### 2.1 static_cast 关键字

`static_cast`是静态转换的意思，也就是在编译期间进行转换，转换失败的话回抛出一个编译错误。



`static_cast`只能用于良性转换，这样的转换风险比较低，一般不会发生什么意外，例如：

* 原有的自动类型转换，比如 short 转 int;

* void 指针和具体类型指针之间的转换，例如`void*`转`int*`，`char*`转`void*`等；
* 有转换构造函数或者类型转换函数的类与其他类型之间的转换，例如`double`转`complex`，`complex`转`double`。



`static_cast`不能用于无关类型之间的转换，因为这些转换都是有风险的，例如：

* 两个具体类型指针的转换，例如`int*`转`double*`，`double*`转`int*`。不同类型数据存储格式不一样，长度也不一样。
* `int`与指针之间的转换。



```c++
// Demo1 - static_cast
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

class Complex
{
public:
	Complex(double r, double i): real(r), imag(i) {}
	operator double() const { return sqrt(real*real + imag*imag); }  // 类型转换函数

private:
	double real; 
	double imag; 
};

void main()
{
	// 自动类型转换
	int m = 1000;
	long n = static_cast<long>(m);   // 宽转换，没有信息丢失
	char ch = static_cast<char>(m);  // 窄转换，可能会丢失信息
	cout << "m = " << m << endl;
	cout << "static_cast<long>(m) = " << n << endl;
	cout << "static_cast<char<(m) = " << ch << endl;

	// void 指针和具体类型指针之间的转换
	void* p1 = static_cast<void*>(new int [10]);  // 将 int* 转换为 void*
	int* p2 = static_cast<int*>(p1);  // 将 void* 转换为 int*

	// 有类型转换函数的类与其他类型之间的转换
	Complex c(12.5, 23.8);
	double d = static_cast<double>(c); // 等同于 double(c); 从而调用 Complex::operator double()
	cout << d << endl;
  
  // 错误的用法
  // float* p3 = static_cast<float*>(p2);  // float* 与 int* 不能转换
  // p3 = static_cast<float*>(98);         // 不能将整数转换为指针
}
```



### 2.2 const_cast 关键字

`const_cast`比较容易理解，它用来去掉表达式的`const`修饰或`volatile`修饰。

也就是说，`const_cast`用来将`const/volatile`类型转换为非`const/volatile`类型。

```c++
// Demo2 - const_cast 
#include <iostream>
using namespace std;

void main()
{
	const int* cn = new int(100);
	int *p = const_cast<int*>(cn);

	// *cn = 123;  // error: read-only variable is not assignable
	*p = 123;

	cout << *cn << endl;  // 123
	cout << *p << endl;   // 123
}
```



### 2.3 reinterpret_cast 关键字

`reinterpret`是重新解释的意思，顾名思义，`reinterpret_cast`这种转换是对二进制位的重新解释，不会借助已有的转换规则来对数据进行调整，非常简单粗暴，风险很高。

`reinterpret_cast`可以被认为是对`static_cast`的一种补充，一些`static_cast`不能完成的转换，就可以使用`reinterpret_cast`来完成，例如：

* 两个具体类型指针的转换；
* int 和指针之间的转换。

```c++
// Demo 3: reinterpret_cast 的危险用法 ： 通常会导致程序崩溃
#include <iostream>
using namespace std;

class A
{
public:
	A(int a, int b): first(a), second(b) {}
private:
	int first;
	int second;
};

void main()
{
	// 将 char* 转换为 float*
	char str[] = "lsl love programming.";
	float* f = reinterpret_cast<float*> (str);
	cout << *f << endl;

	// 将 A* 转换为 unsigned*
	unsigned* u = reinterpret_cast<unsigned*>(new A(1, 2));
	cout << *u << endl;

	// 将 整数 转换为 整数指针
	int* p = reinterpret_cast<int*>(100);
	// 即使编译时不报错，运行时通常也会报错。因为序号为该整数的内存空间，通常处于未分配的状态。
	cout << *p << endl;
}
```



### 2.3.1 reinterpret_cast 用于辅助哈希函数

C++之父 Bjarne Stroustrup 指出：错误的使用 `reinterpret_cast` 很容易导致程序的不安全，只有将转换后的类型值转换回到其原始类型，这样才是正确使用`reinterpret_cast` 方式。

`reinterpret_cast` 的真正价值：用来辅助哈希函数。

```c++
// reinterpret_cast 的真正价值: 用来辅助哈希函数
#include <iostream>

// Returns a hash code based on an address
unsigned short Hash(void* p) 
{
	unsigned int val = reinterpret_cast<unsigned int>(p);
	return (unsigned short)(val ^ (val >> 16));
}

void main() 
{
	int a[20];
	for (int i = 0; i < 20; i++) std::cout << Hash(a + i) << std::endl;
}
```

对整数的操作显然要比对地址操作更方便。在集合中存放整形数值，也要比存放地址更具有扩展性（当然如果存void *扩展性也是一样很高的），唯一损失的可能就是存取的时候整形和地址的转换（这完全可以忽略不计）。



### 2.3.2 指针类型会教导编译器如何解释特定内存地址中的内容

先套用《深度探索C++对象模型》中的一段话，“一个指向字符串的指针是如何地与一个指向整数的指针或一个指向其他自定义类型对象的指针有所不同呢？从内存需求的观点来说，没有什么不同！它们三个都需要足够的内存（并且是相同大小的内存）来放置一个机器地址。指向不同类型的各指针间的差异，既不在其指针表示法不同，也不在其内容（代表一个地址）不同，而是在其所寻址出来的对象类型不同。也就是说，指针类型会教导编译器如何解释某个特定内存地址中的内容及其大小。”



### 2.4 dynamic_cast 关键字

`dynamic_cast`用于在类的继承层次之间进行类型转换，它既允许向上转型(Upcasting，即将派生类转换为基类)，也允许向下转型(Downcasting，将基类转换为派生类)。向上转型是无条件的，不会进行任何检测，所以都能成功。向下转型的理论基础是“派生类对象可以用任何一个基类指针指向它”，从而基类指针可指向派生类，产生了"将基类转换为派生类"的假象。



`dynamic_cast`与`static_cast`是相对的，`dynamic_cast`是动态转换的意思，`static_cast`是静态转换的意思。

`dynamic_cast`会在程序运行期间借助 RTTI 进行类型转换，这就要求基类必须包含虚函数。

`static_cast`在编译期间完成类型转换，能够更加及时地发现错误。



`dynamic_cast`的语法格式为：

```c++
dynamic_cast<newType>(expression)
```



`newType` 和 `expression` 必须同时是指针类型或引用类型。也就是说，`dynamic_cast` 只能用于转换指针类型和引用类型，其他类型(int，double， 数组，类，结构体等)都不行。



* 如果`expression`是指针，转换失败时将返回`nullptr`；
* 如果`expression`是引用，转换失败时将抛出`std::bad_cast`异常。



示例4: `dynamic_cast`向上转型`Upcasting`

```c++
#include <iostream>
using namespace std;

class Base
{
public:
	Base(int bd) : baseData(bd) {}
	int getData() const { return baseData; }
	virtual void func() const { cout << "Calling BaseObject->func()." << endl; }

private:
	int baseData;
};

class Derived: public Base
{
public:
	Derived(int a, int b): Base(a), derivedData(b) {}
	int getData() const { return derivedData; }

private:
	int derivedData;
};

int main()
{
	Derived* pd1 = new Derived(35, 78);
	Base* pb1 = dynamic_cast<Base*>(pd1);
	cout << "pd1 = " << pd1 << endl;
	cout << "pb1 = " << pb1 << endl;

	cout << pb1->getData() << endl;
	pb1->func();

	return 0;
}
```


