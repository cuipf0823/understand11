#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <type_traits>
#include <vector>
#include <map>
#include <typeinfo>
#include <initializer_list>
#include <memory>
#include <stdarg.h>
using namespace std;
namespace Five
{
	//C++11中 强类型枚举  
	enum class Type: char
	{
		General = 1,
		Light,
		Medium,
		Heavy
	};

	//编译时常量
	constexpr int GetConst()
	{
		return 1;
	}

	const int GetRunConst()
	{
		return 1;
	}

	//常量表达式函数要求函数体中只有一条语句 data函数无法通过编译
	/*
	constexpr int data()
	{
		const int i = 1;
		return i;
	}
	*/

	constexpr int sta_data(int x)
	{
		static_assert(0 == 0, "assert failed");
		return x;
	}

	struct Date
	{
		constexpr Date(int y, int m, int d) :year(y), month(m), day(d)
		{

		}

		constexpr int GetYear()
		{
			return year;
		}

		constexpr int GetMonth()
		{
			return month;
		}

		constexpr int GetDay()
		{
			return day;
		}

	private:
		int year;
		int month;
		int day;
	};

	double SumOfFloat(int count, ...)
	{
		va_list ap;
		double sum = 0;
		va_start(ap, count);
		for (int idx = 0; idx < count; ++idx)
		{
			sum += va_arg(ap, double);
		}
		va_end(ap);
		return sum;
	}

	void TestChaperFive()
	{
		
		Type t = Type::Heavy;
//		t = General;   //编译不通过 必须使用强类型名称

		//C++11智能指针的使用
		unique_ptr<int> up1(new int(11)); //无法复制的unique_ptr
//		unique_ptr<int> up2 = up1;        //不能通过编译
		unique_ptr<int> up3 = move(up1);  //目前up3 是数据唯一的智能指针
		cout << *up3 << endl;
		/*
		运行时错误
		cout << *up1 << endl;
		*/
		up3.reset();

		//下面必须使用编译常量，对于运行常量编译不通过
		int arr[GetConst()] = { 0 };
		enum 
		{
			e1 = GetConst(),
			e2
		};

		constexpr Date PRCfound{ 1949, 10, 1 };
		constexpr int foundmonth = PRCfound.GetMonth();
	}

}



