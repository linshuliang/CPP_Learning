# new 和 delete 运算符

## new 运算符

使用 `new` 运算符来为任意的数据类型动态分配内存的通用语法:

```c++
new data_type;
```

在这里，**data-type** 可以是包括数组在内的任意内置的数据类型，也可以是包括类或结构在内的用户自定义的任何数据类型。



例如，我们可以定义一个指向 `double` 类型的指针，然后请求内存，该内存在执行时被分配。

```c++
double* pvalue = new double;  // 为变量请求内存
// 如果自由存储区已被用完，可能无法成功分配内存。
// 所以建议检查 new 运算符是否返回 NULL 指针，并采取以下适当的操作
if(!pvalue)
{
    std::cout << "[Error] out of memory" << std::endl;
    exit(1);
}
```



`malloc()`函数在 C 语言中就出现了，在 C++ 中仍然存在，但建议尽量不要使用 `malloc()` 函数。

`new` 与 `malloc()` 函数相比，其主要的优点是，`new` 不只是分配了内存，它还创建了对象。



在任何时候，当您觉得某个已经动态分配内存的变量不再需要使用时，您可以使用 `delete` 操作符释放它所占用的内存:

```c++
delete pvalue;  // 释放 pvalue 所指向的内存
```



**示例**

```c++
#include <iostream>
#include <iomanip>

int main()
{
	double* pvalue = nullptr;
	pvalue = new double;   // 为变量请求内存
	if (!pvalue)
	{
		std::cout << "[Error] Out Of Memory" << std::endl;
		system("pause"); exit(1);
	}

	*pvalue = 29494.99;  // 在分配的地址存储值
	std::cout << "Value of pvalue : " << std::setprecision(6) << *pvalue << std::endl;
	delete pvalue;  // 释放内存

	system("pause");  return 0;
}
```



## 数组的动态内存分配

二维数组的动态分配，结合 `RAII` 的思想，将二维数组的内存分配和释放封装成了一个类。

```c++
#include <iostream>
#include <iomanip>
#include <exception>

template<typename T>
class TwoDimArray
{
public:
	TwoDimArray() = default;
	TwoDimArray(int r, int c);
	~TwoDimArray();
	void assign(int r, int c, T value);
	void print();

private:
	int _rows;
	int _cols;
	T** _data;
};

template<typename T>
TwoDimArray<T>::TwoDimArray(int r, int c)
{
	this->_rows = r;
	this->_cols = c;

    // 分配空间顺序：第一维 --> 最后一维
	this->_data = new T* [r];
	for (int i = 0; i < r; i++)
	{
		this->_data[i] = new T [c];
	}
}

template<typename T>
TwoDimArray<T>::~TwoDimArray()
{
    // 释放空间顺序：最后一维 --> 第一维
	if (_data != nullptr)
	{
		for (int i = 0; i < this->_rows; i++)
			delete [] this->_data[i];

		delete [] this->_data;
	}
}

template<typename T>
void TwoDimArray<T>::assign(int r, int c, T value)
{
	if(r < this->_rows && c < this->_cols)
		this->_data[r][c] = value;
	else
	{
		throw "Out of range";
	}
}

template<typename T>
void TwoDimArray<T>::print()
{
	for (int i = 0; i < this->_rows; i++)
	{
		for (int j = 0; j < this->_cols; j++)
		{
			std::cout << std::setw(5) << _data[i][j] << "  ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	int rows = 3;
	int cols = 2;
	TwoDimArray<double> arr(rows, cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr.assign(i, j, (i + j) * 2);
		}
	}

	arr.print();

	system("pause");
	return 0;
}
```



三维数组的动态分配，结合 `RAII` 的思想，将三维数组的内存分配和释放封装成了一个类。

```c++
#include <iostream>
#include <iomanip>
#include <exception>

template<typename T>
class ThreeDimArray
{
public:
	ThreeDimArray() = default;
	ThreeDimArray(int channel, int row, int col);
	~ThreeDimArray();
	void assign(int channel, int row, int col, T value);
	void print();

private:
	int _channels;
	int _rows;
	int _cols;
	T*** _data;
};

template<typename T>
ThreeDimArray<T>::ThreeDimArray(int channel, int row, int col)
{
	this->_channels = channel;
	this->_rows = row;
	this->_cols = col;

    // 分配空间顺序：第一维 --> 最后一维
	this->_data = new T** [channel];
	for (int i = 0; i < channel; i++)
	{
		this->_data[i] = new T* [row];
		for (int j = 0; j < row; j++)
		{
			this->_data[i][j] = new T[col];
		}
	}
}

template<typename T>
ThreeDimArray<T>::~ThreeDimArray()
{
    // 释放空间顺序：最后一维 --> 第一维
	if (_data != nullptr)
	{
		for (int i = 0; i < this->_channels; i++)
		{
			for (int j = 0; j < this->_rows; j++)
				delete [] this->_data[i][j];

			delete [] this->_data[i];
		}

		delete[] this->_data;
	}
}

template<typename T>
void ThreeDimArray<T>::assign(int channel, int row, int col, T value)
{
	if (channel < this->_channels && row < this->_rows && col < this->_cols)
		this->_data[channel][row][col] = value;
	else
	{
		throw "Out of range";
	}
}

template<typename T>
void ThreeDimArray<T>::print()
{
	for (int c = 0; c < this->_channels; c++)
	{
		for (int i = 0; i < this->_rows; i++)
		{
			for (int j = 0; j < this->_cols; j++)
			{
				std::cout << std::setw(5) << _data[c][i][j] << "  ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

int main()
{
	int channels = 2;
	int rows = 3;
	int cols = 2;
	ThreeDimArray<double> arr(channels, rows, cols);

	for (int c = 0; c < channels; c++)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				arr.assign(c, i, j, c * 0.1 + (i + j) * 2);
			}
		}
	}

	arr.print();

	system("pause");
	return 0;
}
```

