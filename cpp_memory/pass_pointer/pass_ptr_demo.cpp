#include <iostream>

void getMemory(char** p, int request_size)
{
	*p = new char[request_size];
}

char* getMemory(int request_size)
{
	char* p = new char[request_size];
	return p;
}

void main()
{
	char* arr = nullptr;
	const int request_size = 10;
	getMemory(&arr, request_size);
	for (int i = 0; i < request_size; i++) arr[i] = '1';
	std::cout << arr << std::endl;

	auto arr2 = getMemory(request_size);
	for (int i = 0; i < request_size; i++) arr2[i] = '2';
	std::cout << arr2 << std::endl;

	delete[] arr;
	delete[] arr2;
	system("pause");
}