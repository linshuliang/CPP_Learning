#include <iostream>
#include <string>

void main()
{
	int n = 100;
	std::string* const p = new std::string[n];
	std::string* q = p;

	std::cout << "Input string (end with 'Ctrl + Z, Enter') : " << std::endl;
	std::string s;
	while (std::cin >> s && q != p + n)  // 按下 Ctrl + Z 组合键，再按 Enter, 此时 std::cin >> s 返回 false
	{
		*q = s;
		q++;
	}

	std::cout << "All string : " << std::endl;
	const size_t size = q - p;
	for (int i = 0; i < size; i++)
	{
		std::cout << p[i] << std::endl;
	}
	
	delete[] p;
}