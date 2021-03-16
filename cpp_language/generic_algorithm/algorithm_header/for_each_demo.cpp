#include <iostream>
#include <algorithm>
#include <vector>

/*
template <class _InIt, class _Fn>
_Fn for_each(_InIt _First, _InIt _Last, _Fn _Func) { // perform function for each element [_First, _Last)
    _Adl_verify_range(_First, _Last);
    auto _UFirst = _Get_unwrapped(_First);
    const auto _ULast = _Get_unwrapped(_Last);
    for (; _UFirst != _ULast; ++_UFirst) {
        _Func(*_UFirst);
    }

    return _Func;
}
*/

void main()
{
    std::vector<int> v;
    for (int i = 0; i < 10; i++) v.push_back(i);

    // Count the number of even numbers in the vector by using the for_each function and a lambda
    int evenCount = 0;
    for_each(v.begin(), v.end(), [&](int n) { 
        std::cout << n << (n % 2 == 0 ? " is even" : " is odd") << std::endl;
        evenCount = (n % 2 == 0 ? evenCount + 1 : evenCount);
    });

    std::cout << "There are " << evenCount << " even numbers in the vector" << std::endl;
	system("pause");
}