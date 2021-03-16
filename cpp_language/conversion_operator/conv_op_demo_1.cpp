#include <algorithm>
#include <iostream>

class Complex
{
public:
	Complex() : real(0), image(0) {}
	Complex(double r, double i) : real(r), image(i) {}
	explicit operator double() const;  // 类型转换运算符，禁止隐式的类型转换
	explicit operator int() const;     // 类型转换运算符，禁止隐式的类型转换
	operator int* () const;
	Complex operator + (Complex c1);   // 重载运算符
	Complex operator + (double d);     // 重载运算符
	Complex operator + (int i);        // 重载运算符

private:
	double real;   // 实数部分
	double image;  // 虚数部分
};

Complex::operator double() const
{
	double ret = std::sqrt(std::pow(this->real, 2) + std::pow(this->image, 2));
	return ret;
}

Complex::operator int() const
{
	double ret = std::sqrt(std::pow(this->real, 2) + std::pow(this->image, 2));
	return static_cast<int>(ret);
}

Complex::operator int*() const
{
	double d_ret = std::sqrt(std::pow(this->real, 2) + std::pow(this->image, 2));
	int* ret = new int(d_ret);
	return ret;
}

Complex Complex::operator + (Complex c1)
{
	Complex sum;
	sum.real = this->real + c1.real;
	sum.image = this->image + c1.image;
	return sum;
}

Complex Complex::operator + (double d)
{
	Complex sum;
	sum.real = this->real + d;
	sum.image = this->image;
	return sum;
}

Complex Complex::operator + (int i)
{
	Complex sum;
	sum.real = this->real + i;
	sum.image = this->image;
	return sum;
}

int main()
{
	Complex c1(3, 4.2);

	double d_num = static_cast<double>(c1);
	std::cout << d_num << std::endl;

	// double d2_num = c1;  // 错误，explicit 关键字：禁止隐式的类型变换

	int i_num = static_cast<int>(c1);
	std::cout << i_num << std::endl;

	double d_sum = static_cast<double>(c1 + 6.2);  // 先执行 c1.operator+(6.2), 再执行 operator double()
	std::cout << d_sum << std::endl;

	int i_sum = static_cast<int>(c1 + 6);  // 先执行 c1.operator+(6), 再执行 operator int()
	std::cout << i_sum << std::endl;

	int* c_ptr = c1;  // 先执行隐式的类型变换 operator int*(), 再赋值
	std::cout << *c_ptr << std::endl;
	delete c_ptr;

	system("pause");
	return 0;
}
