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

enum Gener
{
	boy,
	girl
};

class people
{
public:
	people(initializer_list<pair<std::string, Gener> > var_list)
	{
		auto i = var_list.begin();
		for (; i != var_list.end(); ++i)
		{
			data.push_back(*i);
		}
	}
private:
	vector<pair<string, Gener> > data;
};

void FunInit(initializer_list<int> iv)
{

}

class InitListData
{
public:
	InitListData& operator [] (initializer_list<int> l)
	{
		for (auto i = l.begin(); i != l.end(); ++i)
		{
			idx.push_back(*i);
		}
		return *this;
	}

	InitListData& operator = (int v)
	{
		if (idx.empty() != true)
		{
			for (auto i = idx.begin(); i != idx.end(); ++i)
			{
				d.resize((*i > d.size()) ? *i : d.size());
				d[*i - 1] = v;
			}
			idx.clear();
		}
	}

	void Print()
	{
		for (auto i = d.begin(); i != d.end(); ++i)
		{
			cout << *i << " ";
		}
		cout << endl;
	}
private:
	vector<int> idx;
	vector<int> d;   
};

void TestInitData()
{
	InitListData init_d;
	init_d[{2, 3, 5}] = 7;
	init_d[{1, 4, 6, 8}] = 8;
	init_d.Print();
}

vector<int> GetVector()
{
	return { 1, 2 };
}
/*
const vector<int>& GetVectorRef()
{
	return { 3, 5 };
}
*/


//�û��Զ���������
typedef unsigned char uint8;
struct RGBA
{
	uint8 r;
	uint8 g;
	uint8 b;
	uint8 a;
	RGBA(uint8 R, uint8 G, uint8 B, uint8 A = 0):
		r(R),
		g(G),
		b(B),
		a(A)
	{

	}

};

std::ostream& operator << (std::ostream & out, RGBA & col)
{
	return out << "r: " << (int)col.r << " g: " << (int)col.g << " b: " << (int)col.b << " a: " << (int)col.a << endl;
}

RGBA operator "" _C(const char* col, size_t n)
{
	//һ������Ϊn���ַ���col
	const char* p = col;
	const char* end = col + n;
	const char *r, *g, *b, *a;
	r = g = b = a = nullptr;
	for (; p != end; ++p)
	{
		if (*p == 'r')
		{
			r = p;
		}
		else if (*p == 'g')
		{
			g = p;
		}
		else if (*p == 'b')
		{
			b = p;
		}
		else if (*p == 'a')
		{
			a = p;
		}
	}
	if ((r == nullptr) || (g == nullptr) || (b == nullptr))
	{
		throw;
	}
	else if (a == nullptr)
	{
		return RGBA(atoi(r + 1), atoi(g + 1), atoi(b + 1));
	}
	else
	{
		return RGBA(atoi(r + 1), atoi(g + 1), atoi(b + 1), atoi(a + 1));
	}
}

void blend(RGBA& col1, RGBA& col2)
{
	cout << "blend " << endl << col1 << col2 << endl;
}

void blend1(RGBA&& col1, RGBA&& col2)
{
	cout << "blend1 " << endl << col1 << col2 << endl;
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


	people name_12 = { { "tom", boy }, { "lily", girl }, { "kuku", boy } };
	FunInit({ 1, 2 });
	FunInit({});       //���б�
	TestInitData();

	///////////////////////////////////////////////
	RGBA col1(25, 24, 15);
	RGBA col2({ 15, 255, 10, 17 });
	blend(col1, col2);

	blend1("r255 g240 b155"_C, "r12 g255 b10 a7"_C);
}



}
