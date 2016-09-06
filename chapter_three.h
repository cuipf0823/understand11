#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <type_traits>
#include <vector>
#include <map>
#include <initializer_list>
using namespace std;

namespace three
{
//������ʹ�û����Ա������ʽ
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



//�ƶ�����
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
	//�ƶ����캯��
	HasPtrMem(HasPtrMem && h) : d_(h.d_)
	{
		h.d_ = nullptr;     //��ʵ�δ��ݽ���������ָ���Ա�ÿ�
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

//��ֵ����
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
	//�ƶ����캯��
	Moveable(Moveable&& mo)
	{
		i = mo.i;
		mo.i = nullptr;
		cout << "move copy " << endl;
	}

public:
	int* i;
};

class HugeMem
{
public:
	HugeMem(int size) : sz(size > 0 ? size : 1)
	{
		c = new int[sz];
	}
	~HugeMem()
	{
		delete[] c;
	}
	//�ƶ��������캯��
	HugeMem(HugeMem && hm) : sz(hm.sz), c(hm.c)
	{
		hm.c = nullptr;
	}
	int* c;
	int sz;
};

class Moveable2
{
public:
	Moveable2() :i(new int(3)), h(1024)
	{

	};
	~Moveable2()
	{
		delete i;
	};
	//ǿ��תΪ��ֵ���Ե����ƶ����캯��
	Moveable2(Moveable2 && m) :i(m.i), h(move(m.h))
	{
		m.i = nullptr;
	}
	int* i;
	HugeMem h;
};

Moveable2 GetMoveable2Temp()
{
	Moveable2 tmp = Moveable2();
	cout << hex << "Huge Mem from " << __func__ << " @" << tmp.h.c << endl;
	return tmp;
}

//forward������ʹ��
void Runcode(int && m)
{
	cout << "rvalue ref" << endl;
}
void Runcode(int& m)
{
	cout << "lvalue ref" << endl;
}
void Runcode(const int && m)
{
	cout << "const rvalue ref" << endl;
}
void Runcode(const int & m)
{
	cout << "const lvalue ref" << endl;
}

template <typename T>
void PerfectForward(T &&t)
{
	Runcode(forward<T>(t));
}

class ConvertTo
{

};

class Convertable
{
public:
	//��ʾת����convertto��������ת����
	explicit operator ConvertTo () const
	{
		cout << "operator ()" << endl;
		return ConvertTo();
	}
};

void FunCon(ConvertTo ct)
{

}


//�б��ʼ��
int a_list[] = { 1, 2, 3 };
int b_list[] {1, 2, 4};
vector<int> c_vector{ 1, 5, 6 };
vector<int> d_vector = { 1, 2, 3 };
map<int, float> e_map {{1, 1.2}, { 1, 2.3 }, { 3, 3.6 }};
map<int, float> f_map = { { 1, 1.2 }, { 1, 2.3 }, { 3, 3.6 } };

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

// 	Moveable a;
// 	Moveable c(move(a)); //������ƶ����캯��
// 	cout << *a.i << endl; //�������д��� ��ʱa.i����ΪNULL������a����������Ҫ������

	Moveable2 a(GetMoveable2Temp());
	cout << hex << "Huge Mem from " << __func__ << " @" << a.h.c << endl;

	int a1 = 0;
	int b1 = 0;
	const int c1 = 1;
	const int d = 0;
	PerfectForward(a1);
	PerfectForward(move(b1));
	PerfectForward(c1);
	PerfectForward(move(d));

	Convertable c;
	ConvertTo ct(c);				//ֱ�ӳ�ʼ��
	//ConvertTo ct2 = c;			//���������ʼ�� ����ʧ��
	ConvertTo ct3 = static_cast<ConvertTo>(c); //ֱ��ǿ��ת��
	//FunCon(c);	                    //���������ʼ��ʧ��
}



}
