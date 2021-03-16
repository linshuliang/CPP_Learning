// vector::data
#include <iostream>
#include <vector>

void main()
{
    std::vector<int> myvector(5);
    int* p = myvector.data();

    *p = 10;
    ++p;
    *p = 20;
    p[2] = 100;  // p[2] 等同于 *(p + 2)

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < myvector.size(); ++i) 
		std::cout << ' ' << myvector[i];  // 10, 20, 0, 100, 0
    std::cout << '\n';
	system("pause");
}