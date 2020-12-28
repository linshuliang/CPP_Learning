# std::vector

## 存储

### 访问容器存储的大小

```c++
size_type size() const noexcept;
```

Returns the number of elements in the vector.

This is the number of actual objects held in the vector, which is not necessarily equal to its storage `capacity`.



```c++
size_type capacity() const noexcept;
```

Return size of the allocated storage capacity.

This capacity is not necessarily equal to the vector size. It can be equal or greater, with the extra space allowing to accommodate for growth without the need to reallocate on each insertion.

When this capacity is exhausted and more is needed, it is automatically expanded by the container (reallocating its storage space). The theoretical limit on the size of a vector is given by member `std::vector::max_size()`.

The capacity of a vector can be explicitly altered by calling member `std::vector::reserve()`. 



```c++
size_type max_size() const noexcept;
```

Returns the maximum number of elements that the vector can hold.

这是一个固定的数，是一个 vector 能存储元素的最大个数。



```c++
bool empty() const noexcept;
```

Returns whether the vector is empty. 等同于判断 `size() == 0`



### 改变容器存储的大小

```c++
void resize(size_type n);
void resize(size_type n, const value_type& val);
```

Resizes the container so that it contains *n* elements.

If *n* is smaller than the current container `size`, the content is reduced to its first *n* elements, removing those beyond (and destroying them).

If *n* is greater than the current container `size`, the content is expanded by inserting at the end as many elements as needed to reach a size of *n*. If *val* is specified, the new elements are initialized as copies of *val*, otherwise, they are value-initialized. （如果指定了 val，则用val来填充，否则用默认值来填充） 

If *n* is also greater than the current container [capacity](http://www.cplusplus.com/vector::capacity), an automatic reallocation of the allocated storage space takes place.（如果resize 的尺寸大于capacity，还会重新分配存储空间，将现有值拷贝到新的分配空间中）

Notice that this function changes the actual content of the container by inserting or erasing elements from it.



```c++
void reserve(size_type n);
```

Requests a change in capacity.

If `n` is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to `n`.

In all other cases, this function call does not cause a reallocation and the vector capacity is not affected.

如果 n 大于当前容量，则会为此 vector 重新分配内存空间以增加容量。否则，此函数不会做任何操作。











