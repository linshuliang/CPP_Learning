# private 关键字

## 2 解疑

### 2.1 为什么要将某些类成员定义为 private 类型？

如果将类中的属性定义为 `public`，当属性的名称/类型等发生改变时，所有调用该属性的代码都需要修改。

将类成员定义为 `private` ，则外部只能通过 `public` 接口函数来访问，只要接口不变，代码就不需要改变。

因此，将类成员定义为 `private` 有利于代码的维护。

当`private`成员变量发生变化时，只需要修改该类的代码，而不影响类外的其他函数或变量。



### 2.2 类的构造函数可以声明为 private 吗？

（1）如果一个类的构造函数只有一个，且访问属性为 `private`，则编译可以通过。但如果类的内部没有专门创建实例的代码，则无法创建任何实例。

```c++
#include <iostream>

class Base
{
private:
	Base()
	{
		std::cout << "Construct Base" << std::endl;
	}
};

void main()
{
	// Base b;  // 无法访问
}
```



（2）如果一个类的构造函数只有一个，且访问属性为`private`，则可通过静态函数来创建类实例。

```c++
#include <iostream>

class Base
{
public:
	static Base* newAnObject();
    
    // 当拷贝构造函数为 private 时，无法将创建的实例传递到外部。
    // 当拷贝构造函数为 public 时，可通过这种方法来创建实例。
	static Base makeAnObject();  

private:
	Base();
	Base(const Base&);
};

Base::Base()
{
	std::cout << "Default Constructor" << std::endl;
}

Base::Base(const Base&)
{
	std::cout << "Copy Constructor" << std::endl;
}

Base* Base::newAnObject()
{
	return new Base();
}

Base Base::makeAnObject()
{
	return Base();
}

void main()
{
	// Base b;  // 无法访问
	Base* bp = Base::newAnObject();
	delete bp;

	Base::makeAnObject();  // 正确
	// Base bc = Base::makeAnObject();  // 错误，拷贝构造函数为 private
}
```





