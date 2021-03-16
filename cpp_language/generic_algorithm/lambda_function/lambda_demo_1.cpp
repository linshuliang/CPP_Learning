#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

// 去重
void elimDups(std::vector<std::string>& words)
{
	// 按字典
	std::sort(words.begin(), words.end());
	// 重排，使得每个单词只出现一次，返回指向不重复区域之后一个位置的迭代器
	auto end_unique = std::unique(words.begin(), words.end());
	// 删除重复的单词
	words.erase(end_unique, words.end());
}

void main()
{
	std::vector<std::string> strs = { "the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle" };
	elimDups(strs);

	// 按长度排序, 小 -> 大  
	std::stable_sort(strs.begin(), strs.end(), [](const std::string& a, const std::string& b) { return a.size() < b.size(); });

	// 获取一个迭代器，指向第一个满足 size() >= sz 的元素
	const int sz = 3;
	auto wc = std::find_if(strs.begin(), strs.end(), [sz](const std::string& a) { return a.size() > sz; });

	int bigger_count = strs.end() - wc;
	std::cout << "Bigger Count : " << bigger_count << std::endl;

	for (auto it = wc; it != strs.end(); it++)
		std::cout << *it << std::endl;
}