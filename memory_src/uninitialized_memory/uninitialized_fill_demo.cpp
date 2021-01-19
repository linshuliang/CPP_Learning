#include <iostream>
#include <memory>  // std::allocator, std::uninitialized_copy

void main()
{
    std::allocator<std::string> str_alloc;
    const int alloc_num = 10;
    std::string* sptr = str_alloc.allocate(alloc_num);

    std::uninitialized_fill(sptr, sptr+ alloc_num, "Hi");

    // 输出字符串
    for (int i = 0; i < alloc_num; i++) std::cout << *(sptr + i) << std::endl;

    // 将已赋值的对象执行析构
    auto q = sptr + alloc_num;
    while (q != sptr) str_alloc.destroy(--q);

    // 当所有元素被销毁后，我们可以用 deallocate 来释放内存
    str_alloc.deallocate(sptr, alloc_num);
}