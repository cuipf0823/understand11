#ifndef CHAPTER_SEVEN_H
#define CHAPTER_SEVEN_H
#include <iostream>
namespace seven
{

class TestDemo
{
public:
	TestDemo(int a, int b) :num(new int(a)), age(new int(b))
	{

	}
// 		TestDemo(int a, int b)
// 		{
// 			num = new int(a);
// 			age = new int(b);
// 		}
	~TestDemo()
	{
		//不需要判断num 是否为空
		delete num;
		delete age;
	}
private:
	int * const num;
	int * const age;
};

/*
class Info
{
public:
	Info()
	{
		InitInfo();
	}
	Info(int i):i_(i)
	{
		InitInfo()
	}
	Info(int i, double d): i_(i), d_(d)
	{
		InitInfo();
	}
private:
	void InitInfo(){};
	int i_ = 0;
	double d_ = 0.0;
}
*/
class Info
{
public:
	Info()
	{
		InitInfo();
	}
	Info(int i):Info()
	{
		i_ = i;
	}
	Info(int i, double d):Info()
	{
		i_ = i;
		d_ = d;
	}
private:
	void InitInfo(){};
	int i_ = 0;
	double d_ = 0.0;
};

template <class T>
void Swap(T& a, T& b)
{
	T tmp(move(a));
	a = move(b);
	b = move(tmp);
}

void test_chapter_seven()
{
	cout << "==================Seven================" << endl;
	int i = 10;
	int j = 100;
	int w = (i = 100, j += 100);
	std::cout << i << endl;
	std::cout << w << endl;

	TestDemo demo(10, 20);
}


}
#endif
