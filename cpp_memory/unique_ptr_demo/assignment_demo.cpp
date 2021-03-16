#include <iostream>
#include <memory>

void main()
{
	std::unique_ptr<int> foo;
	std::unique_ptr<int> bar;

	// unique_ptr& operator=(unique_ptr&&);
	foo = std::unique_ptr<int>(new int(100));

	// unique_ptr& operator=(unique_ptr&&);
	bar = std::move(foo);

	if (foo)
		std::cout << "foo : " << *foo << std::endl;
	else
		std::cout << "foo is empty" << std::endl;

	if (bar)
		std::cout << "bar : " << *bar << std::endl;
	else

		std::cout << "bar is empty" << std::endl;
}