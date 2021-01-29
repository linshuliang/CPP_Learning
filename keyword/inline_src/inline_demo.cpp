#include <iostream>

inline const char *num_check(int v) 
{ 
	return (v % 2 > 0) ? "奇" : "偶"; 
} 

void main() 
{ 
	for (int i = 0; i < 100; i++) 
		std::cout << i << " " << num_check(i) << std::endl;
	system("pause");
}