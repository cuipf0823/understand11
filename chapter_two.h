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
*	变长参数宏的使用
*/
#define LOG(...) \
{ \
	fprintf(stderr, "%s: line %d :", __FILE__, __LINE__);\
	fprintf(stderr, __VA_ARGS__); \
	fprintf(stderr, "\n"); \
}

void macro()
{
	//C99中包含的，C++11继承下来
	cout << "Standard Clib: " << __STDC_HOSTED__ << endl; //是否包含完整的C库 1包含
	cout << "Standard C: " << __STDC__ << endl;			  //编译器的实现是否和C标准一样
	cout << "ISO/IEC " << __STDC_ISO_10646__ << endl;	  //编译环境符合的某个版本的ISO/IEC的标准

	//打印函数名
	cout << __func__ << endl;
	cout << __FUNCTION__ << endl;

	//C++11允许__func__运用到类和结构体中
	TestMacro tm;
	cout << tm.name << endl;
	int x = 3;
	LOG("x = %d", x);

	//long long类型
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
*	自定义实现assert_static
*/
#define assert_static(e) \
do\
{\
	enum { assert_static__ = 1 / (e) };  \
}while (0)


/*
*  异常处理
*/
void Throw() { throw 1; }

void NoBlockThrow()
{
	Throw();
}

//C++11 noexecpt修饰的函数抛出异常，编译器可以选择直接使用std::terminate()函数来终止程序的运行；
//这比基于异常处理机制的throw在效率上高一些

//void excpt_func() noexcept(常量表达式) 常量表达式 == true表示不会抛出异常 ==false抛出异常
void BlockThrow() noexcept
{
	//Throw();
}

/*
*  处于安全 C++11标准中析构默认是noexcept(ture),可以阻止异常的扩散
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

	//不抛出异常，阻止了异常的扩散

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
*  C++11中变量的初始化
*/
struct Init
{
	int a = 1;
	double b{ 1.2 };
	//std::string str1("abc");  //编译不通过
};

/*
*	非静态成员的sizeof
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
	cout << sizeof(p.hand) << endl;	       //C++98 通过 C++11 通过
	cout << sizeof(People::all) << endl;   //C++98 通过 C++11 通过
	cout << sizeof(People::hand) << endl;  //C++98 错误 C++11 通过
	cout << sizeof(((People*)0)->hand) << endl; //C++98中获取没有类实例类的非静态成员大小的方法
}

/*
*	friend的扩展使用
*/

class FriendTest;
typedef FriendTest FT;
class Expend1
{
	friend class FriendTest;    //C++98 通过 C++11 通过
};
class Expend2
{
	friend FriendTest;	        //C++98 失败 C++11 通过
};
class Expend3
{
	friend FT;				    //C++98 失败 C++11 通过
};
//friend可以为类模板声明友元
template <typename T>
class Expend4
{
	friend T;
};

Expend4<FriendTest> ef;		   //类型FriendTest在这里是Expend4的友元
Expend4<int> pi;			   //int类型模板参数，友元声明被忽略

/*
*	c++11中final和override的使用
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
//	void func(); //无法通过编译
};

struct Base1
{
	virtual void Turing() = 0;
	virtual void VNeumann(int g) = 0;
};

struct DerivedMid: public Base1
{
	void Turing() override;	     //
//	void VNeumann() override;	 //无法通过编译 参数不一样
	void VNeumann(int g) override;
};

/*
*	模板函数的默认模板参数
*/

template<typename T1, typename T2 = int>
class DefClass1;
/*
template<typename T1 = int, typename T2>
class DefClass2;						  //编译错误
*/
template<typename T, int i = 0>
class DefClass3;
/*
template<int i = 0, typename T>
class DefClass4;				           //编译错误
*/
template<typename T1 = int, typename T2>
void DefFunc(T1 a, T2 b);
template<int i = 0, typename T>
void DefFunc(T a);

/*
	局部和匿名类型作模板实参
*/

/*
template <typename T>
class X { };
template <typename T>
void TempFun(T t){};

struct A{ } a;
struct {int i;} b; //b为匿名类型变量   

typedef struct {int i; } B;  //B为匿名类型


void test_template()
{
	struct C
	{

	} c;
	X<A> x1;		//C++98 通过 C++11通过
	X<B> x2;		//C++98 错误 C++11通过
	X<C> x3;		//C++98 错误 C++11通过
	TempFun(a);		//C++98 通过 C++11通过
	TempFun(b);		//C++98 错误 C++11通过
	TempFun(c);		//C++98 错误 C++11通过
}
*/

void chapter_two()
{
	assert((SMAX - 1) == (C99 | ExtInt | SAssert | NoExcept));
	assert_static((SMAX - 1) == (C99 | ExtInt | SAssert | NoExcept));
	//C++11 中引入了static_assert 接收两个参数，一个是断言表达是返回bool值，一个是警告信息
	int a = 0;
	int b = 0;
	static_assert(sizeof(a) == sizeof(b), "the parameters should have same width");
	macro();
	test_except();
	test_size_of();
}

}
