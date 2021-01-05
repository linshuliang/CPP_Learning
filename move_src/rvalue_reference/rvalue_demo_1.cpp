#include <iostream>
#include <utility>

void main()
{
	int i = 20;
	int& lvalue_ref_1 = i;  // 左值引用
	std::cout << lvalue_ref_1 << std::endl;
	// int& lvalie_ref_2 = 50;  // 50 是右值，无法从 int 转换为 int&

	int&& rvalue_ref_1 = 50;  // 右值引用
	std::cout << rvalue_ref_1 << std::endl;

	// int&& rvalue_ref_2 = i;  // ERROR: 无法将左值绑定到右值引用
	int&& rvalue_ref_2 = std::move(i);
	std::cout << rvalue_ref_2 << std::endl;

	// int& lvalue_ref_3 = i * 3;  // ERROR: i * 3 是一个右值，无法将右值绑定到左值引用
	int&& rvalue_ref_3 = i * 3;
	std::cout << rvalue_ref_3 << std::endl;
}