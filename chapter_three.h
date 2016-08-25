#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
using namespace std;

<<<<<<< HEAD
namespace three
{
//派生类使用基类成员函数方式
class Base
{
public:
	void f(double i)
	{
		cout << "Base: " << i << endl;
	}
};
class Derived : public Base
{
public:
	using Base::f;
	void f(int i)
=======
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
>>>>>>> 5e55f846aacfa6169bda814fae7451a9d363e617
	{
		cout << "Derived: " << i << endl;
	}
};

<<<<<<< HEAD


//移动语义
class HasPtrMem
{
public:
	HasPtrMem(): d_(new int(0))
	{
		cout << "Construct: " << ++n_cstr_ << endl;
	}
	HasPtrMem(const HasPtrMem& h) : d_(new int(*h.d_))
	{
		cout << "Copy construct: " << ++n_cptr_ << endl;
	}
	//移动构造函数
	HasPtrMem(HasPtrMem && h) : d_(h.d_)
	{
		h.d_ = nullptr;     //将实参传递进来变量的指针成员置空
		cout << "move construct: " << ++n_mvtr_ << endl;
	}
	~HasPtrMem()
	{
		cout << "Destruct: " << ++n_dstr_ << endl;
		delete d_;
	}

public:
	int* d_;
	static int n_cstr_;
	static int n_dstr_;
	static int n_cptr_;
	static int n_mvtr_;
};

int HasPtrMem::n_cstr_ = 0;
int HasPtrMem::n_dstr_ = 0;
int HasPtrMem::n_cptr_ = 0;
int HasPtrMem::n_mvtr_ = 0;

HasPtrMem GetTemp()
{
	return HasPtrMem();
}

HasPtrMem GetTempMove()
{
	HasPtrMem h;
	cout << "Resource from " << __func__ << ":" << hex << h.d_ << endl;
	return h;
}


void TestChaperThree()
{
	Base b;
	b.f(4.5);
	Derived derived;
	derived.f(89.90);
	derived.f(678);

	//HasPtrMem mem = GetTemp();
	cout << "============================" << endl;
	HasPtrMem mem_move = GetTempMove();
	cout << "Resource from " << __func__ << ":" << hex << mem_move.d_ << endl;
}

}
=======
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
>>>>>>> 5e55f846aacfa6169bda814fae7451a9d363e617
