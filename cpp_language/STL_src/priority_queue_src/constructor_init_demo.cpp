// std::priority_queue init constructor
#include <iostream>
#include <queue>

void main()
{
	std::vector<int> v = { 10, 20, 50, 30, 7 };
	std::priority_queue<int> pq(std::less<int>(), v);

	while (!pq.empty())
	{
		std::cout << pq.top() << std::endl;
		pq.pop();
	}
	system("pause");
}