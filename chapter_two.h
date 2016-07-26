#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
using namespace std;

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
#define log(...) { \
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
	log("x = %d", x);

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
		funA();
	}
	catch (...)
	{
		cout << "caught funA" << endl;
	}
}

/*
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
}