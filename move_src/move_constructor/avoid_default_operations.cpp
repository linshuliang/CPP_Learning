#include <string>
#include <map>

struct libraryPersonInfo
{
public:
	void assignment(const std::string& name, const std::map<int, int>& req)
	{
		this->name_ = name;
		this->req_ = req;
	}

private:
	std::string name_;
	std::map<int, int> req_;
};

void main()
{
	libraryPersonInfo person;
	person.assignment("lin", std::map<int, int>(5, 1));
}