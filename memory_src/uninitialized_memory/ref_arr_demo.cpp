#include <iostream>
#include <utility>

void main()
{
	int arr[] = { 1, 2, 5 };
	const auto arr_size = std::size(arr);
	// int& int_ref = arr;       // ERROR : int_ref �������� int&, arr �������� int[3]�����Ͳ�ƥ��
	// int& ref[3] = {3, 8, 6};  // ERROR : ������ʹ�����õ�����

	int* int_ptr = new int(88);
	int (&ref_arr)[arr_size] = arr;

	for (int i = 0; i < arr_size; i++)
		std::cout << arr[i] << std::endl;
}