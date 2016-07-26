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
*	�䳤�������ʹ��
*/
#define log(...) { \
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
	log("x = %d", x);

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
void BlockThrow() noexcept
{
	Throw();
}

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
}

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
}