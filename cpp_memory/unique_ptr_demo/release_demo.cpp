#include <iostream>
#include <memory>

void main()
{
	std::unique_ptr<int> up(new int);
	*up = 10;

	int* manual_pointer = up.release();  // ��ʱ up ���ͷſ���Ȩ��manual_pointer �ӹ�ָ��Ŀ���Ȩ
	std::cout << "The stored value of manual_pointer : " << *manual_pointer << std::endl;
	delete manual_pointer;  // new �������ڴ������ʾɾ�������򽫵����ڴ�й©
}