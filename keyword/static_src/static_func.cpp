#include <iostream>
#include <cstdlib>

static int getInt()
{
	return rand() % 100;
}

void main()
{
	for (int i = 0; i < 10; i++) std::cout << getInt() << std::endl;
	system("pause");
}