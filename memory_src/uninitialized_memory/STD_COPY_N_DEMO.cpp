// std::copy
#include <iostream>     // std::cout
#include <algorithm>    // std::copy
#include <vector>       // std::vector

void main() {
    int myints[] = { 10,20,30,40,50,66,70 };
    std::vector<int> myvector(7);

    auto ret = std::copy_n(myints, 7, myvector.begin());
    std::cout << *(myvector.data() + 6) << std::endl;  // 70
    std::cout << *(--ret) << std::endl;                // 70

    std::cout << "myvector contains:";
    for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
        std::cout << ' ' << *it;

    std::cout << '\n';
}