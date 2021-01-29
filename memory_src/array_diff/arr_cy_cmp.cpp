#include <iostream>
#include <cstring>

void main()
{
	char a[] = "hello";
	char b[10];
	strcpy(b, a);

	int len = strlen(b);
	char* p = new char[len];
	strcpy(p, b);

	if (strcmp(p, b) == 0) std::cout << "The same " << std::endl;
	system("pause");
}