#include <string>
#include <cstring>
#include <vector>
#include <iostream>

// 将输入字符串 str 以 delim 为分隔符进行分割
std::vector<std::string> str_split(const std::string& str, const std::string delim)
{
	std::vector<std::string> ret;
	if (str.empty()) return ret;

	// 将 string 转换为 char*
	char* str_chars = new char[str.length() + 1];
	strcpy(str_chars, str.c_str());
	
	char* delim_chars = new char[delim.length() + 1];
	strcpy(delim_chars, delim.c_str());

	// char* strtok(char* str, const char* delimiters);
	char* p = strtok(str_chars, delim_chars);  // 第一次调用时，参数 str 为一个C字符串，其第一个字符用作扫描令牌的起始位置
	while (p)
	{
		std::string s = p;
		ret.push_back(s);
		p = strtok(nullptr, delim_chars);  // 在随后的调用中，该函数需要一个空指针，并使用最后一个标记结束后的位置作为扫描的新起始位置
	}
	
	delete[] str_chars;
	delete[] delim_chars;
	return ret;
}

void main()
{
	std::string s = "- This, a sample string.";

	std::vector<std::string> res = str_split(s, " ,.-");
	for (int i = 0; i < res.size(); ++i)
	{
		std::cout << res[i] << std::endl;
	}
}