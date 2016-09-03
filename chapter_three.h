#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
using namespace std;

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
	{
		cout << "Derived: " << i << endl;
	}
};



//移动语义
class HasPtrMem
{
public:
	HasPtrMem() : d_(new int(0))
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

//右值引用
class Moveable
{
public:
	Moveable():i(new int(2))
	{

	}
	~Moveable()
	{
		delete i;
	}
	Moveable(const Moveable& o)
	{
		i = new int(*o.i);
		cout << "Copied" << endl;
	}
	//移动构造函数
	Moveable(Moveable&& mo)
	{
		i = mo.i;
		mo.i = nullptr;
		cout << "move copy " << endl;
	}

public:
	int* i;
};




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

	Moveable a;
	Moveable c(move(a)); //会调用移动构造函数
	cout << *a.i << endl; //编译运行错误 此时a.i被置为NULL，但是a的声明周期要到结束
}



}
