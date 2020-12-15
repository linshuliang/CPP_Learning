#include <iostream>
#define DEBUG

#define MIN(a,b) (((a)<(b)) ? a : b)

int main()
{
#ifdef DEBUG
    std::cerr << "Trace: Inside main function" << std::endl;
#endif

#if 0
    /* 这部分不会进行编译 */
    std::cout << "HELLO C++" << std::endl;
#endif

    int i = 100;
    int j = 30;
    std::cout << "The minimum is " << MIN(i, j) << std::endl;

#ifdef DEBUG
    std::cerr << "Trace: Coming out of main function" << std::endl;
#endif

    return 0;
}