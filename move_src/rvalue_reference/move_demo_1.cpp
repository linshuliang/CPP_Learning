#include <iostream>
#include <utility>  // move
#include <string>
#include <vector>

void main()
{
	std::string bar = "bar-string";
	std::string&& bar_rvalue_ref = std::move(bar);
	std::cout << "bar : " << bar << std::endl;  // bar-string
	std::cout << "right value reference of bar : " << bar_rvalue_ref << std::endl;  // bar-string

	std::vector<std::string> my_vec;
	// void std::vector::push_back(const value_type& val); 
	my_vec.push_back(bar);

	// void std::vector::push_back(value_type&& val);
	my_vec.push_back(bar_rvalue_ref);
	for (auto it = my_vec.begin(); it != my_vec.end(); it++) std::cout << *it << "  ";
	std::cout << std::endl;
}
