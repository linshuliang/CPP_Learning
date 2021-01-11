#include <iostream>
#include <memory>

void main()
{
	std::unique_ptr<int> up;  // empty
	up.reset(new int);        // takes ownership of pointer
	*up = 5;
	std::cout << *up << std::endl;

	up.reset(new int);  // deletes managed object, acquire new pointer
	*up = 10;
	std::cout << *up << std::endl;

	up.reset();  // deletes managed object
}
