#include <iostream>
#include <iomanip>

int main()
{
	double* pvalue = nullptr;
	pvalue = new double;   // Ϊ���������ڴ�
	if (!pvalue)
	{
		std::cout << "[Error] Out Of Memory" << std::endl;
		system("pause"); exit(1);
	}

	*pvalue = 29494.99;  // �ڷ���ĵ�ַ�洢ֵ
	std::cout << "Value of pvalue : " << std::setprecision(6) << *pvalue << std::endl;
	delete pvalue;  // �ͷ��ڴ�

	system("pause");  return 0;
}