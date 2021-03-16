#include <iostream>
#include <string>
#include <memory>
#include <utility>

class Data
{
public:
	Data(int i) : data_(i) {}
	void Print() { std::cout << "[Data::Print] " << data_ << std::endl; }
	void Display(std::string s="") const { std::cout << s << " [Data::Display] " << data_ << std::endl; }  // ��������ֻ�ܵ��� const ����
	void Destroy() { data_ = 0; }
	// ��� const ������С���޸������Ա���ߵ����˷� const ���������������ҳ��������

private:
	int data_;
};

const Data& func(const Data& d)
{
	// d.Print();  // ERROR : ���������Ա���������ݵ��޶��������������� const Data
	d.Display("func");  // d �� const ���ͱ�������ֻ�ܵ��� const ����
	Data a = d;
	a.Print();
	return d;
}

void main()
{
	Data d1(10);
	auto l_ret = func(d1);  // d1 ����ֵ��const�����ܽ�����ֵ��ʼ��
	l_ret.Display("main");

	auto r_ret = func(Data{ 15 });  // Data { 15 } ����ֵ�� const�����ܽ�����ֵ��ʼ��
	r_ret.Display("main");
}