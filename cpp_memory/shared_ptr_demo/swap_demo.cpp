#include <iostream>
#include <memory>

void main()
{
	std::shared_ptr<int> foo(new int{ 20 });
	std::shared_ptr<int> foo2 = foo;
	std::shared_ptr<int> bar(new int{ 10 });
	foo.swap(bar);
	std::cout << *foo << ", " << foo.use_count() << std::endl;  // 10, 1
	std::cout << *bar << ", " << bar.use_count() << std::endl;  // 20, 2
}