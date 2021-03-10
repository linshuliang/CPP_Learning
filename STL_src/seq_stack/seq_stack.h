#include <vector>
#include <iostream>
#include <exception>

template<class T>
class SeqStack
{
public:
	SeqStack();
	bool empty();
	int size();
	T& top();
	void push(const T&);
	T& pop();
	
private:
	std::vector<T> m_elements;
	static int m_max_size;
};

template<class T>
int SeqStack<T>::m_max_size = 100;

template<class T>
SeqStack<T>::SeqStack()
{
	this->m_elements = std::vector<T>();
}

template<class T>
bool SeqStack<T>::empty()
{
	return (m_elements.size() == 0);
}

template<class T>
int SeqStack<T>::size()
{
	return m_elements.size();
}

template<class T>
T& SeqStack<T>::top()
{
	if (this->empty())
		throw std::out_of_range("stack is empty");
	else
		return m_elements.back();
}

template<class T>
void SeqStack<T>::push(const T& ele)
{
	if (m_elements.size() >= m_max_size)
	{
		std::cout << "stack is full already" << std::endl;
	}
	else
	{
		m_elements.push_back(ele);
	}
}

template<class T>
T& SeqStack<T>::pop()
{
	if (this->empty())
		throw std::out_of_range("stack is empty");
	else
	{
		T ele = m_elements.back();
		m_elements.pop_back();
		return ele;
	}
}
