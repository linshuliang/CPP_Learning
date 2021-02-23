// Demo - 动态绑定
#include <iostream>

class A
{
public:
	virtual void vfunc1()
	{
		std::cout << "A.size() : " << sizeof(*this) << std::endl;
		// 16, 其中两个整数为8个字节，64位程序的vptr为64位，也即8个字节
	}

	virtual void vfunc2()
	{
		std::cout << "sizeof(int) : " << sizeof(this->m_data1) << std::endl;  // 4
	}

	void func1();
	void func2();

private:
	int m_data1;
	int m_data2;
};

class B : public A
{
public:
	void vfunc1()
	{
		std::cout << "B.size() : " << sizeof(*this) << std::endl;
		// 24, 其中三个整数为12个字节，64位程序的vptr为64位，也即8个字节
	}

	void vfunc2()
	{
		std::cout << "sizeof(void*) : " << sizeof(void*) << std::endl;  // 8
	}

	void func1();
	void func2();

private:
	int m_data3;
};

class C : public B 
{
public:
	virtual void vfunc2()
	{
		std::cout << "C.size() : " << sizeof(*this) << std::endl;
		// 32, 其中五个整数为20个字节，64位程序的vptr为64位，也即8个字节
	}
	void func2();
private:
	int m_data1, m_data4;
};

void main()
{
	A a_instance;
	a_instance.vfunc1();

	B b_instance;
	b_instance.vfunc1();

	C c_instance;
	c_instance.vfunc2();

	system("pause");
}