#include <iostream>

template<class T>
class strVec
{
public:
	strVec() : data_(nullptr), size_(0) {};  // 默认构造函数
	strVec(T* d) : data_(d), size_(0) {};
	strVec(size_t s) : data_(nullptr), size_(s) {};
	strVec(T* d, size_t s) : data_(d), size_(s) {};
	strVec(const strVec& rhs);      // copy constructor
	strVec(strVec&& rhs) noexcept;  // move constructor
	~strVec();  // 析构函数

private:
	T* data_;
	size_t size_;
};

template<class T>
strVec<T>::strVec(const strVec& rhs)
{
	std::cout << "Call Copy Constructor" << std::endl;
	data_ = new T(rhs.size_);
	strVec<T> &lhs = *this;
	lhs.size_ = rhs.size_;
	std::copy_n(rhs.data_, rhs.size_, lhs.data_);  // copy data
}

template<class T>
strVec<T>::strVec(strVec&& rhs) noexcept
{
	std::cout << "Call Move Constructor" << std::endl;
	strVec<T>& lhs = *this;
	lhs.size_ = rhs.size_;
	lhs.data_ = rhs.data_;  // move data
	rhs.size_ = 0;          // 恢复为默认情况
	rhs.data_ = nullptr;    // 恢复为默认情况
}

template<class T>
strVec<T>::~strVec()
{
	if (data_)  // 判断是否为空
	{  
		delete[] data_;
	}
}

void main()
{
	strVec<char> sv(new char[10], 10);
	strVec<char> sv2(sv);   // 拷贝构造
	strVec<char> sv3 = sv;  // 拷贝赋值
	strVec<char> sv4(std::move(sv));  // 移动构造
}
