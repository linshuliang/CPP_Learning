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

// һ����ԣ�deleter�ķ���ֵ����Ϊvoid���β�����Ϊdata_type*
void deleter(sample* sp)
{
	std::cout << "Call deleter." << std::endl;
	delete[] sp->data;
}

void main()
{
	std::shared_ptr<sample> sp1(new sample());           // Call Destructor to free memory���ڴ�й©
	std::shared_ptr<sample> sp2(new sample(), deleter);  // Call deleter to free memory����ȷ�ͷ�����ռ�
}