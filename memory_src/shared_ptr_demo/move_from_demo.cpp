#include <iostream>
#include <memory>

void main() 
{
	std::shared_ptr<int> foo;
	std::shared_ptr<int> bar(new int(10));

	// copy assignment
	// template<class U>
	// shared_ptr& operator=(const shared_ptr<U>& x) noexcept;
	foo = bar; 

	// copy assignment
	// template<class U>
	// shared_ptr& operator=(const shared_ptr<U>& x) noexcept;
	bar = std::make_shared<int>(20);
	std::cout << "*bar: " << *bar << '\n';
	std::cout << "bar.use_count(): " << bar.use_count() << '\n';  // 1

	std::unique_ptr<int> up(new int(30));

	// move from other pointer
	// template<class U>
	// shared_ptr& operator=(unique_ptr<U>&& x);
	foo = std::move(up);

	std::cout << "*foo: " << *foo << '\n';
	std::cout << "foo.use_count(): " << foo.use_count() << std::endl;  // 1
}