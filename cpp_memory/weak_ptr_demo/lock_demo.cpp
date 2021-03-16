#include <iostream>
#include <memory>

template<class T>
void acess_weak_ptr(const std::weak_ptr<T>& wp)
{
	std::shared_ptr<T> sp = wp.lock();
	if (!sp)
		std::cout << "The weak_ptr is empty or expired." << std::endl;
	else
	{
		std::cout << "The contained value in weak_ptr : " << *sp << std::endl;
	}
}

void main()
{
	std::weak_ptr<int> wp;
	acess_weak_ptr<int>(wp);

	std::shared_ptr<int> sp1 = std::make_shared<int>(10);
	wp = sp1;
	acess_weak_ptr<int>(wp);
}