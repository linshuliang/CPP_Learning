#include <iostream>
#include <utility>  // std::size()
#include <memory>  // std::allocator, std::uninitialized_copy

template <class _Ty, size_t _Size>
constexpr size_t mySize(const _Ty(&)[_Size]) noexcept {
    return _Size;
}

void main()
{
    const char* v[] = { "This", "is", "an", "example" };
    auto v_size = std::size(v);
    
    std::allocator<std::string> str_alloc;
    const int alloc_num = 10;
    std::string* sptr = str_alloc.allocate(alloc_num);

    std::uninitialized_copy(v, v + v_size, sptr);
    
    // 输出字符串
    for (int i = 0; i < v_size; i++) std::cout << *(sptr + i) << std::endl;

    // 将已赋值的对象执行析构
    auto q = sptr + v_size;
    while (q != sptr) str_alloc.destroy(--q);

    // 当所有元素被销毁后，我们可以用 deallocate 来释放内存
    str_alloc.deallocate(sptr, alloc_num);
}