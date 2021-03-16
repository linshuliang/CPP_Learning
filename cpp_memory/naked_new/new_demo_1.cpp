#include <iostream>
#include <iomanip>

int main()
{
	double* pvalue = nullptr;
	pvalue = new double;   // 为变量请求内存
	if (!pvalue)
	{
		std::cout << "[Error] Out Of Memory" << std::endl;
		system("pause"); exit(1);
	}

	*pvalue = 29494.99;  // 在分配的地址存储值
	std::cout << "Value of pvalue : " << std::setprecision(6) << *pvalue << std::endl;
	delete pvalue;  // 释放内存

	system("pause");  return 0;
}