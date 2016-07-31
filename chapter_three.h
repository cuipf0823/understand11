#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
using namespace std;

namespace NameThree
{

/*
	继承构造函数
*/

class Base
{
public:
	void func(double f)
	{
		cout << "Base: " << f << endl;
	}
};

//派生类即存在结构double类型的func又存在接受int类型的
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