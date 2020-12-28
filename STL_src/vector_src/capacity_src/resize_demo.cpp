// resizing vector
// void std::vector::resize(size_type n, value_type val = value_type());
#include <iostream>
#include <vector>

void main()
{
    std::vector<int> myvector;

    // set some initial content:
    for (int i = 1; i < 10; i++) myvector.push_back(i);

    // If n is smaller than the current container size, the content is reduced to its first  n elements
    // remove those beyond (and destroying them)
    myvector.resize(5);

    // If n is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of n.
    // If val is specificed, the new elements are initialized as copies of val, otherwise, they are value-initialized.
    myvector.resize(8, 100);

    // If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
    myvector.resize(12);

    std::cout << "myvector contains:";
    for (int i = 0; i < myvector.size(); i++)
        std::cout << ' ' << myvector[i];
    std::cout << '\n';
}