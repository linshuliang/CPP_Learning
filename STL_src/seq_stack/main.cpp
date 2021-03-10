#include "seq_stack.h"
#include <cmath>

void main()
{
	SeqStack<int> ss;
	for (int i = 0; i < 110; i++)
	{
		ss.push(rand());
	}
	
	std::cout << "ss.size() = " << ss.size() << std::endl;

	while (!ss.empty())
	{
		std::cout << ss.top() << "  ";
		ss.pop();
	}
}