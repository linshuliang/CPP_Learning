#include <iostream>
#include <utility>  // std::pair, std::make_pair

struct M2 {   // bad: incomplete set of copy/move/destructor operations
public:
    M2() = default;
    M2(std::pair<int, int>* d) : data(d) {};
    // ... no copy or move operations ...
    // ~M2() { delete data; }
    void print();

private:
    std::pair<int, int>* data;
};

void M2::print()
{
    if (this->data)
    {
        std::cout << data->first << " " << data->second << std::endl;
    }
}

void main()
{
    std::pair<int, int> pp = std::make_pair<int, int>(1, 1);
    M2 x(&pp);
    x.print();
}