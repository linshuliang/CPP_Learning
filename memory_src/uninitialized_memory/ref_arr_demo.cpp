#include <iostream>
#include <utility>

void main()
{
	int arr[] = { 1, 2, 5 };
	const auto arr_size = std::size(arr);
	// int& int_ref = arr;       // ERROR : int_ref 的类型是 int&, arr 的类型是 int[3]，类型不匹配
	// int& ref[3] = {3, 8, 6};  // ERROR : 不允许使用引用的数组

	int* int_ptr = new int(88);
	int (&ref_arr)[arr_size] = arr;

	for (int i = 0; i < arr_size; i++)
		std::cout << arr[i] << std::endl;
}