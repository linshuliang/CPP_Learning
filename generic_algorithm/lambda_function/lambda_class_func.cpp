#include <algorithm>  // std::for_each
#include <iostream>
#include <vector>

class FunctorClass
{
public:
	FunctorClass(int& e) : m_evenCount(e) {}

	void operator()(int n)
	{
		std::cout << n;
		std::cout << (n % 2 == 0 ? " is even" : " is odd") << std::endl;
		m_evenCount = (n % 2 == 0) ? m_evenCount + 1 : m_evenCount;
	}

private:
	int& m_evenCount;
};

void main()
{
	std::vector<int> v;
	for (int i = 1; i < 10; i++) v.push_back(i);
	int evenCount = 0;
	std::for_each(v.begin(), v.end(), FunctorClass(evenCount));
	std::cout << "Even Count : " << evenCount << std::endl;
}
