// shared_ptr destructor demo : customized deleter
#include <iostream>
#include <memory>

class sample
{
public:
	sample()
	{
		std::cout << "Call constructor." << std::endl;
		data = new int[10];
	}

	~sample()
	{
		std::cout << "Call Destructor." << std::endl;
	}

	int* data;
};

// 一般而言，deleter的返回值类型为void，形参类型为data_type*
void deleter(sample* sp)
{
	std::cout << "Call deleter." << std::endl;
	delete[] sp->data;
}

void main()
{
	std::shared_ptr<sample> sp1(new sample());           // Call Destructor to free memory，内存泄漏
	std::shared_ptr<sample> sp2(new sample(), deleter);  // Call deleter to free memory，正确释放数组空间
}