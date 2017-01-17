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