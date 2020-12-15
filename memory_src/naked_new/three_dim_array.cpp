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
	this->_data = new T * *[channel];
	for (int i = 0; i < channel; i++)
	{
		this->_data[i] = new T * [row];
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
				delete[] this->_data[i][j];

			delete[] this->_data[i];
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