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

	this->_data = new T* [r];
	for (int i = 0; i < r; i++)
	{
		this->_data[i] = new T [c];
	}
}

template<typename T>
TwoDimArray<T>::~TwoDimArray()
{
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