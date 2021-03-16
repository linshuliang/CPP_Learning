#include <iostream>

// reinterpret_cast 的最大用处：用来辅助哈希函数
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
	system("pause");
}
