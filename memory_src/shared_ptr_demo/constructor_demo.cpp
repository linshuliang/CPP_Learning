// shared_ptr constructor example
#include <iostream>
#include <memory>

struct C { int* data; };

void main() 
{
	// default constructor
	// constexpr shared_ptr() noexcept;
	std::shared_ptr<int> p1;

	// from null pointer
	// constexpr shared_ptr(nullptr_t) : shared_ptr() {}
	std::shared_ptr<int> p2(nullptr);

	// from pointer
	// template<class U>
	// explict shared_ptr(U* p);
	std::shared_ptr<int> p3(new int);

	// pointer + deleter
	// template<class U, class D>
	// shared_ptr(U* p, D del)
	std::shared_ptr<int> p4(new int, std::default_delete<int>());
	
	// pointer + deleter + allocator
	// template<class U, class D, class Alloc>
	// shared_ptr(U* p, D del, Alloc alloc>
	std::shared_ptr<int> p5(new int, [](int* p) {delete p;}, std::allocator<int>());
	
	// copy constructor
	// template<class U>
	// shared_ptr(const shared_ptr<U>& x) noexcept;
	std::shared_ptr<int> p6(p5);

	// move constructor
	// template<class U>
	// shared_ptr(shared_ptr<U>&& x) noexcept;
	std::shared_ptr<int> p7(std::move(p6));

	// template<class U>
	// shared_ptr(unique_ptr<U>& x);
	std::shared_ptr<int> p8(std::unique_ptr<int>(new int));

	std::shared_ptr<C> obj(new C);
	obj->data = new int(10);
	int* one_int = new int(20);

	// aliasing constructor
	// template<class U>
	// shared_ptr(const shared_ptr<U>& x, element_type* p) noexcept;
	std::shared_ptr<int> p9(obj, one_int);

	std::cout << "p1: "  << p1.use_count()  << '\n';  // 0
	std::cout << "p2: "  << p2.use_count()  << '\n';  // 0
	std::cout << "p3: "  << p3.use_count()  << '\n';  // 1
	std::cout << "p4: "  << p4.use_count()  << '\n';  // 1
	std::cout << "p5: "  << p5.use_count()  << '\n';  // 2
	std::cout << "p6: "  << p6.use_count()  << '\n';  // 2 -> 0
	std::cout << "p7: "  << p7.use_count()  << '\n';  // 2
	std::cout << "p8: "  << p8.use_count()  << '\n';  // 1
	std::cout << "obj: " << obj.use_count() << '\n';  // 2
	std::cout << "p9: "  << p9.use_count()  << '\n';  // 2
	std::cout << "*p9: " << *p9             << '\n';  // 20
	delete p9.get();  // 因为 p9 不管理 one_int 的生存期，所以必须显式删除
}