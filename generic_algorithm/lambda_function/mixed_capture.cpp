#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

void print_strs(std::vector<std::string>& words, std::vector<std::string>::size_type sz, std::ostream& os = std::cout, char c = ' ')
{
	// 除了 c 是赋值捕获（显式）外，其他变量都是引用捕获（隐式）
	std::for_each(words.begin(), words.end(), [&, c](const std::string& s) { os << "[print_strs] " << s << c; });
}

void echo_strs(std::vector<std::string>& words, std::vector<std::string>::size_type sz, std::ostream& os = std::cout, char c = ' ')
{
	// 除了 os 是引用捕获（显式）外，其他变量都是赋值捕获（隐式）
	std::for_each(words.begin(), words.end(), [=, &os](const std::string& s) { os << "[echo_strs] " << s << c; });
}

void main()
{
	std::vector<std::string> strs = { "i", "am", "so", "handsome" };
	print_strs(strs, strs.size());
	echo_strs(strs, strs.size());
}