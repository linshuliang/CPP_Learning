// std::priority_queue range constructor
#include <iostream>
#include <queue>
#include <string>

void main() 
{
	std::string words[] = { "one", "two", "three", "four" };
	std::priority_queue<std::string> ps(std::begin(words), std::end(words));
	std::cout << "由大至小" << std::endl;
	while (!ps.empty())
	{
		std::cout << ps.top() << "  ";
		ps.pop();
	}
	std::cout << std::endl;

	std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string> > reverse_ps(std::begin(words), std::end(words));
	std::cout << "由小至大" << std::endl;
	while (!reverse_ps.empty())
	{
		std::cout << reverse_ps.top() << "  ";
		reverse_ps.pop();
	}
	std::cout << std::endl;

	system("pause");
}