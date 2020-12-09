#include <iostream>

template<typename T>
class Array
{
public:
    explicit Array(size_t arr_size)
    {
        _arr_data = new T[arr_size];
    }

    void assign(size_t i, T value)
    {
        _arr_data[i] = value;
    }

    T operator [] (size_t i)
    {
        return _arr_data[i];
    }

    ~Array()
    {
        if (_arr_data != nullptr)
            delete[] _arr_data;
    }

private:
    T* _arr_data;
};

int main()
{
    int arr_size = 100;
    Array<int> arr(arr_size);
    for (int i = 0; i < arr_size; i++)
    {
        arr.assign(i, std::pow(i, 2));
    }

    for (int i = 0; i < arr_size; i++)
        std::cout << arr[i] << std::endl;

	system("pause");
	return 0;
}