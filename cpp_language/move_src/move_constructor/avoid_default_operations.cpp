#include <iostream>
#include <string>
#include <map>

struct libraryPersonInfo
{
public:
	void assignment(const std::string& name, const std::map<int, int>& req)
	{
		this->name_ = name;
		this->req_ = req;
		std::cout << "Name : " << name << std::endl;
		std::cout << "Value : ";
		for (auto it = req.begin(); it != req.end(); it++)
		{
			std::cout << it->first << " " << it->second << " ";
		}
		std::cout << std::endl;
	}

private:
	std::string name_;
	std::map<int, int> req_;
};

void main()
{
	libraryPersonInfo person;
	std::string name = "lin";
	std::map<int, int> req;
	req[5] = 1;
	person.assignment(name, req);
}