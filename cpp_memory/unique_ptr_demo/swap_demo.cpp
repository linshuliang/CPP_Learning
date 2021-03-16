#include <iostream>
#include <memory>

void main()
{
	std::unique_ptr<int> foo(new int{ 10 });
	std::unique_ptr<int> bar(new int{ 20 });

	foo.swap(bar);

	std::cout << "foo : " << *foo << std::endl;  // 20
	std::cout << "bar : " << *bar << std::endl;  // 10
}