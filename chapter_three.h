#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
using namespace std;

namespace NameThree
{

/*
	�̳й��캯��
*/

class Base
{
public:
	void func(double f)
	{
		cout << "Base: " << f << endl;
	}
};

//�����༴���ڽṹdouble���͵�func�ִ��ڽ���int���͵�
class Derived : public Base
{
public:
	using Base::func;
	void func(int i)
	{
		cout << "Derived: " << i << endl;
	}
};

void test_construct()
{
	Base b;
	b.func(4.52);

	Derived d;
	d.func(4.59);
	d.func(145);
};

void chapter_three()
{
	test_construct();
}

}