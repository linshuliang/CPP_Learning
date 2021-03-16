#include <iostream>
#include <memory>  // std::allocator, std::uninitialized_copy

void main()
{
    std::allocator<std::string> str_alloc;
    const int alloc_num = 10;
    std::string* sptr = str_alloc.allocate(alloc_num);

    std::uninitialized_fill(sptr, sptr+ alloc_num, "Hi");

    // ����ַ���
    for (int i = 0; i < alloc_num; i++) std::cout << *(sptr + i) << std::endl;

    // ���Ѹ�ֵ�Ķ���ִ������
    auto q = sptr + alloc_num;
    while (q != sptr) str_alloc.destroy(--q);

    // ������Ԫ�ر����ٺ����ǿ����� deallocate ���ͷ��ڴ�
    str_alloc.deallocate(sptr, alloc_num);
}