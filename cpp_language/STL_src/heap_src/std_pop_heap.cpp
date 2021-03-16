#include <algorithm>  // std::make_heap
#include <iostream>
#include <vector>

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
	/* Ð¡¶¥¶Ñ
	*        5
	*    15     10
	* 30    20
	*/

	std::pop_heap(mv.begin(), mv.end(), std::greater<int>());
	mv.pop_back();
	print_vec(mv);
	/* Ð¡¶¥¶Ñ
	*       10
	*    15    20
	* 30    
	*/
}
