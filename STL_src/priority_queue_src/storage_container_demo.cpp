// std::priority_queue 可选择 std::vector 之外的类作为存储容器，比如 std::deque
#include <iostream>
#include <queue>
#include <deque>
#include <string>

void main()
{
	std::string words[] = { "one", "three", "five" };
	std::priority_queue<std::string, std::deque<std::string>> pq(std::begin(words), std::end(words));
	pq.emplace("six");

	while (!pq.empty())
	{
		std::cout << pq.top() << "  ";
		pq.pop();
	}
	std::cout << std::endl;
	system("pause");
}