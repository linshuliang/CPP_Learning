#include <iostream>
#include <memory>

void main()
{
	std::unique_ptr<int> up(new int);
	*up = 10;

	int* manual_pointer = up.release();  // 此时 up 将释放控制权，manual_pointer 接管指针的控制权
	std::cout << "The stored value of manual_pointer : " << *manual_pointer << std::endl;
	delete manual_pointer;  // new 出来的内存必须显示删除，否则将导致内存泄漏
}