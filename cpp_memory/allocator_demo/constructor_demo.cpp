#include <iostream>
#include <memory>
#include <string>

void main()
{
	std::allocator<std::string> alloc;
	int n = 100;  // 大小
	std::string* const p = alloc.allocate(n);

	std::string* q = p; // q指向最后构造元素之后的位置

	alloc.construct(q++, 10, 'c');  // *q 为 cccccccccc
	alloc.construct(q++);           // *q 为空字符串
	alloc.construct(q++, "hi");     // *q 为 hi

	size_t str_num = q - p;
	std::cout << "construct string number : " << str_num << std::endl;  // 3

	std::cout << "First contructed string : "    << *p << std::endl;
	std::cout << "Acess uninitialized memory : " << *q << std::endl;  // 访问未初始化的内存，有可能发生灾难性的后果

	// 由 contruct 创建的对象，必须用 destroy 来析构
	while (q != p) alloc.destroy(--q);

	// 当所有元素被销毁后，我们可以用 deallocate 来释放内存
	alloc.deallocate(p, n);
}