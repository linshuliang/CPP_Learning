// shared_ptr 循环引用会导致内存泄漏
#include <iostream>
#include <memory>

class parent;
class children;

class parent
{
public:
	~parent() { std::cout << "[Parent] Call Destructor" << std::endl; }

public:
	std::weak_ptr<children> children_;
};

class children
{
public:
	~children() { std::cout << "[Children] Call Destructor" << std::endl; }

public:
	std::weak_ptr<parent> parent_;
};

void main()
{
	std::shared_ptr<parent> p(new parent());
	std::shared_ptr<children> c(new children());

	p->children_ = c;
	c->parent_ = p;

	std::cout << "p.use_count() = " << p.use_count() << std::endl;  // 1
	std::cout << "c.use_count() = " << c.use_count() << std::endl;  // 1
}  // 程序退出，p 和 c 的引用计数变为0，自动释放