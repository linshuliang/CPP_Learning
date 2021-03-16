#include <iostream>
#include <memory>

struct cla
{
	int a;
	int b;
};

void main()
{
	std::shared_ptr<int> foo1(new int);
	std::shared_ptr<int> bar1(new int(10));
	*foo1 = *bar1 * 2;
	std::cout << "*foo1: " << *foo1 << std::endl;  // 20
	std::cout << "*bar1: " << *bar1 << std::endl;  // 10

	std::shared_ptr<cla> foo;
	std::shared_ptr<cla> bar(new cla);

	// template<typename U>
	// shared_ptr& operator=(const shared_ptr<U>&);
	foo = bar;

	foo->a = 10;
	bar->b = 20;
	if (foo) std::cout << "foo: " << foo->a << ", " << foo->b << std::endl;  // 10, 20
	if (bar) std::cout << "bar: " << bar->a << ", " << bar->b << std::endl;  // 10, 20
}