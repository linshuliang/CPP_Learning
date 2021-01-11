#include <iostream>
#include <memory>

void main()
{
	std::unique_ptr<int> p = std::make_unique<int>(1);
	// std::unique_ptr<int> p_copy = p;  // Error, std:unique_ptr& std::unique_ptr(const unique_ptr&) = delete;
	std::unique_ptr<int> q = std::move(p);

	if (!p) std::cout << "p is now an nullptr" << std::endl;

	p.reset(new int{ 2 });
	std::cout << "The pointer has been reset to : " << *p << std::endl;
}