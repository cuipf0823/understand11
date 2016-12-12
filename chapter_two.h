#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
using namespace std;
namespace NameTwo
{

struct TestMacro
{
	TestMacro() : name(__func__)
	{

	}
	const char* name;
};

/*
*	�䳤�������ʹ��
*/
#define LOG(...) \
{ \
	fprintf(stderr, "%s: line %d :", __FILE__, __LINE__);\
	fprintf(stderr, __VA_ARGS__); \
	fprintf(stderr, "\n"); \
}

void macro()
{
	//C99�а����ģ�C++11�̳�����
	cout << "Standard Clib: " << __STDC_HOSTED__ << endl; //�Ƿ����������C�� 1����
	cout << "Standard C: " << __STDC__ << endl;			  //��������ʵ���Ƿ��C��׼һ��
	cout << "ISO/IEC " << __STDC_ISO_10646__ << endl;	  //���뻷�����ϵ�ĳ���汾��ISO/IEC�ı�׼

	//��ӡ������
	cout << __func__ << endl;
	cout << __FUNCTION__ << endl;

	//C++11����__func__���õ���ͽṹ����
	TestMacro tm;
	cout << tm.name << endl;
	int x = 3;
	LOG("x = %d", x);

	//long long����
	long long ll_min = LLONG_MIN;
	long long ll_max = LLONG_MAX;
	unsigned long long ull_max = ULLONG_MAX;
	cout << ll_min << " " << ll_max << " " << ull_max << endl;
	cout << sizeof(long long) << endl;

}

enum FeatureSupports
{
	C99 = 0x0001,
	ExtInt = 0x0002,
	SAssert = 0x0004,
	NoExcept = 0x0008,
	SMAX = 0x0010
};

/*
*	�Զ���ʵ��assert_static
*/
#define assert_static(e) \
do\
{\
	enum { assert_static__ = 1 / (e) };  \
}while (0)


/*
*  �쳣����
*/
void Throw() { throw 1; }

void NoBlockThrow()
{
	Throw();
}

//C++11 noexecpt���εĺ����׳��쳣������������ѡ��ֱ��ʹ��std::terminate()��������ֹ��������У�
//��Ȼ����쳣������Ƶ�throw��Ч���ϸ�һЩ

//void excpt_func() noexcept(�������ʽ) �������ʽ == true��ʾ�����׳��쳣 ==false�׳��쳣
void BlockThrow() noexcept
{
	//Throw();
}

/*
*  ���ڰ�ȫ C++11��׼������Ĭ����noexcept(ture),������ֹ�쳣����ɢ
*/
struct A
{
	~A() { throw 1;  }
};

struct B
{
	~B() noexcept(false) { throw 2; }
};

struct C
{
	B b;
};

int funA() { A a; }
int funB() { B b; }
int funC() { C c; }

int test_except()
{
	try
	{
		Throw();
	}
	catch (...)
	{
		cout << "Found Throw." << endl;
	}

	try
	{
		NoBlockThrow();
	}
	catch (...)
	{
		cout << "Throw is not blocked" << endl;
	}
	try
	{
		BlockThrow();
	}
	catch (...)
	{
		cout << "Found throw 1. " << endl;
	}

	try
	{
		funB();
	}
	catch (...)
	{
		cout << "caught funB" << endl;
	}

	try
	{
		funC();
	}
	catch (...)
	{
		cout << "caught funC" << endl;
	}

	//���׳��쳣����ֹ���쳣����ɢ

	try
	{
//		funA();
	}
	catch (...)
	{
		cout << "caught funA" << endl;
	}
}

/*
*  C++11�б����ĳ�ʼ��
*/
struct Init
{
	int a = 1;
	double b{ 1.2 };
	//std::string str1("abc");  //���벻ͨ��
};

/*
*	�Ǿ�̬��Ա��sizeof
*/

struct People
{
public:
	int hand;
	static People* all;
};

void test_size_of()
{
	People p;
	cout << sizeof(p.hand) << endl;	       //C++98 ͨ�� C++11 ͨ��
	cout << sizeof(People::all) << endl;   //C++98 ͨ�� C++11 ͨ��
	cout << sizeof(People::hand) << endl;  //C++98 ���� C++11 ͨ��
	cout << sizeof(((People*)0)->hand) << endl; //C++98�л�ȡû����ʵ����ķǾ�̬��Ա��С�ķ���
}

/*
*	friend����չʹ��
*/

class FriendTest;
typedef FriendTest FT;
class Expend1
{
	friend class FriendTest;    //C++98 ͨ�� C++11 ͨ��
};
class Expend2
{
	friend FriendTest;	        //C++98 ʧ�� C++11 ͨ��
};
class Expend3
{
	friend FT;				    //C++98 ʧ�� C++11 ͨ��
};
//friend����Ϊ��ģ��������Ԫ
template <typename T>
class Expend4
{
	friend T;
};

Expend4<FriendTest> ef;		   //����FriendTest��������Expend4����Ԫ
Expend4<int> pi;			   //int����ģ���������Ԫ����������

/*
*	c++11��final��override��ʹ��
*/

class Object
{
public:
	virtual void func() = 0;
};

class Base : public Object
{
	virtual void func() final;
};

class Derived : public Base
{
//	void func(); //�޷�ͨ������
};

struct Base1
{
	virtual void Turing() = 0;
	virtual void VNeumann(int g) = 0;
};

struct DerivedMid: public Base1
{
	void Turing() override;	     //
//	void VNeumann() override;	 //�޷�ͨ������ ������һ��
	void VNeumann(int g) override;
};

/*
*	ģ�庯����Ĭ��ģ�����
*/

template<typename T1, typename T2 = int>
class DefClass1;
/*
template<typename T1 = int, typename T2>
class DefClass2;						  //�������
*/
template<typename T, int i = 0>
class DefClass3;
/*
template<int i = 0, typename T>
class DefClass4;				           //�������
*/
template<typename T1 = int, typename T2>
void DefFunc(T1 a, T2 b);
template<int i = 0, typename T>
void DefFunc(T a);

/*
	�ֲ�������������ģ��ʵ��
*/

/*
template <typename T>
class X { };
template <typename T>
void TempFun(T t){};

struct A{ } a;
struct {int i;} b; //bΪ�������ͱ���   

typedef struct {int i; } B;  //BΪ��������


void test_template()
{
	struct C
	{

	} c;
	X<A> x1;		//C++98 ͨ�� C++11ͨ��
	X<B> x2;		//C++98 ���� C++11ͨ��
	X<C> x3;		//C++98 ���� C++11ͨ��
	TempFun(a);		//C++98 ͨ�� C++11ͨ��
	TempFun(b);		//C++98 ���� C++11ͨ��
	TempFun(c);		//C++98 ���� C++11ͨ��
}
*/

void chapter_two()
{
	assert((SMAX - 1) == (C99 | ExtInt | SAssert | NoExcept));
	assert_static((SMAX - 1) == (C99 | ExtInt | SAssert | NoExcept));
	//C++11 ��������static_assert ��������������һ���Ƕ��Ա���Ƿ���boolֵ��һ���Ǿ�����Ϣ
	int a = 0;
	int b = 0;
	static_assert(sizeof(a) == sizeof(b), "the parameters should have same width");
	macro();
	test_except();
	test_size_of();
}

}
