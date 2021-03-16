#include <algorithm>  // std::make_heap
#include <iostream>
#include <vector>
#include <cmath>      // pow

template<class T>
void print_vec(const std::vector<T>& mv)
{
	for (auto var : mv) std::cout << var << "  ";
	std::cout << std::endl;
}

void main()
{
	std::vector<int> mv = { 10, 30, 5, 15, 20 };

	std::make_heap(mv.begin(), mv.end(), std::greater<int>());
	print_vec(mv);
	/* С����
	*        5
	*    15     10
	* 30    20
	*/

	mv.push_back(60);
	std::push_heap(mv.begin(), mv.end(), std::greater<int>());
	print_vec(mv);
	/* С����
	*              5
	*      15              10
	*  30      20      60
	*/

	// mv.push_back(3);
	// mv.push_back(7);
	// std::push_heap(mv.begin(), mv.end(), std::greater<int>());
	// print_vec(mv);
	/* ������ĩβ�����Ԫ�ظ�������1ʱ���ٵ���push_heap������п��ܲ��Ƕ�
	*                5 
	*         7             10
	*     15     20     60       3
	* 30
	*/

	mv.push_back(3);
	mv.push_back(7);
	std::push_heap(mv.begin(), mv.end() - 1, std::greater<int>());
	std::push_heap(mv.begin(), mv.end(), std::greater<int>());
	print_vec(mv);
	/* ������ĩβ�����Ԫ�ظ�������1ʱ������ push_heap �Ĵ�������ĩβ�����Ԫ�ظ���ʱ�������Ϊ��
	*                3
	*         7             5
	*     15     20     60       10
	* 30
	*/

	mv.insert(mv.begin(), 101);
	std::push_heap(mv.begin(), mv.end(), std::greater<int>());
	print_vec(mv);
	// �������Ԫ�ص�λ�ò���������ĩβ��������Ϊ��
	// 101  3  7  5  15  20  60  10  30
}
