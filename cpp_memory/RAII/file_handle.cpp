#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <memory>

std::unique_ptr<std::vector<std::string>> read_lines_from_file(std::string& file_name)
{
	std::unique_ptr<std::vector<std::string>> lines(new std::vector<std::string>);
	std::ifstream file_handle(file_name, std::ifstream::in);
	const int line_max_size = 256;
	char line[line_max_size];

	while (file_handle.good() && !file_handle.eof())
	{
		file_handle.getline(line, line_max_size);
		lines->push_back(line);
	}

	file_handle.close();
	return lines;
}

void main()
{
	const std::string file_name = "../memory_src/RAII/array_demo.cpp";
	auto lines = read_lines_from_file(const_cast<std::string&>(file_name));
	int lines_rows = lines->size();
	std::cout << file_name.c_str() << " contains " << lines_rows << " rows." << std::endl;
	system("pause");
}