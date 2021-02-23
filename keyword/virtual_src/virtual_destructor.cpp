#include <iostream>

class Base
{
public:
	Base()
	{
		std::cout << "Construct Base" << std::endl;
	}

	virtual ~Base()
	{
		std::cout << "Destruct Base" << std::endl;
	}

private:
	int i;
};

class Inherit : public Base
{
public:
	Inherit()
	{
		std::cout << "Construct Inherit" << std::endl;
	}

	~Inherit()
	{
		std::cout << "Destruct Inherit" << std::endl;
	}

private:
	int num;
};

void main()
{
	Base *bi = new Inherit();
	delete bi;

	Base *b = new Base();
	delete b;

	system("pause");
}

/*
Construct Base
Construct Inherit
Destruct Inherit
Destruct Base
Construct Base
Destruct Base
*/