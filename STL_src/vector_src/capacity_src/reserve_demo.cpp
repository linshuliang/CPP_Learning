// vector::reserve
#include <iostream>
#include <vector>

void main()
{
    std::vector<int>::size_type sz;
    std::vector<int> foo;
    sz = foo.capacity();
    std::cout << "making foo grow:\n";
    for (int i = 0; i < 100; ++i) {
        foo.push_back(i);
        if (sz != foo.capacity()) {
            sz = foo.capacity();
            std::cout << "capacity changed: " << sz << '\n';
        }
    }

    std::vector<int> bar;
    bar.reserve(100);   // this is the only difference with foo above
    sz = bar.capacity();
    std::cout << "Current capacity: "<< sz << std::endl;

    for (int i = 0; i < 100; ++i) {
        bar.push_back(i);
        if (sz != bar.capacity()) 
        {
            sz = bar.capacity();
            std::cout << "capacity changed: " << sz << '\n';
        }
    }
}