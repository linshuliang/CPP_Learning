// uninitialized demo
#include <iostream>
#include <utility>  // std::size()
#include <memory>   // std::allocator, std::uninitialized_copy

void main()
{
    const char* v[] = { "This", "is", "an", "example" };
    auto v_size = std::size(v);

    std::allocator<std::string> str_alloc;
    const int alloc_num = 10;
    std::string* sptr = str_alloc.allocate(alloc_num);

    std::uninitialized_copy_n(v, v_size, sptr);

    // ����ַ���
    for (int i = 0; i < v_size; i++) std::cout << *(sptr + i) << std::endl;

    // ���Ѹ�ֵ�Ķ���ִ������
    auto q = sptr + v_size;
    while (q != sptr) str_alloc.destroy(--q);

    // ������Ԫ�ر����ٺ����ǿ����� deallocate ���ͷ��ڴ�
    str_alloc.deallocate(sptr, alloc_num);
}