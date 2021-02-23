#include <iostream>

class A 
{
private:
	int a;
public:
	void setA(int x) { a = x; }
	int getA() { return a; }
};
class B :public A 
{
private:
	int b;
public:
	void setB(int x) { b = x; }
	int getB() { return b; }
};

void main() 
{
	A a1;
	B b1;
	a1.setA(1);
	b1.setA(2);
	std::cout << "a1 = " << a1.getA() << std::endl;  // 1
	std::cout << "b1 = " << b1.getA() << std::endl;  // 2

	// �����������ֵ���������
	a1 = b1;  // A& A::operator=(const A&);
	std::cout << "a1 = " << a1.getA() << std::endl;  // 2
	std::cout << "b1 = " << b1.getA() << std::endl;  // 2
	
	a1.setA(10);
	std::cout << "a1 = " << a1.getA() << std::endl;  // 10
	std::cout << "b1 = " << b1.getA() << std::endl;  // 2

	// �����������ĵ�ַ��ֵ������ָ�롣
	A* ap = &b1;
	std::cout << "*ap = " << ap->getA() << std::endl; // 2

	// ������������ʼ�������������á�
	A& ac = b1;
	std::cout << "ac = " << ac.getA() << std::endl;   // 2

	// b1 = a1;      // ERROR : �޷��ѻ������ֵ�����������
	// B* bp = &a1;  // ERROR : �޷����������ĵ�ַ��ֵ��������ָ��
	// B& bc = a1;   // ERROR : �޷�������������ʼ��������������

	system("pause");
}


