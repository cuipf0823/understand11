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



	//变长参数模板
	template<int...A>
	class NonTypeTemplate
	{

	};
	//实例化
	NonTypeTemplate<1, 0, 3> vint;

	//Args是一个模板参数包表示0个或者多个模板类型参数
	//rest函数参数包 表示0个或者多个函数参数
	template <typename T, typename... Args>
	void foo(const T& t, const Args& ... rest)
	{
		std::cout << sizeof ...(Args) << endl;	  //参数类型的数目
		std::cout << sizeof ...(rest) << endl;	  //函数参数的数目
	}
	
	template<typename T>
	ostream& print(ostream& os, const T& t)
	{
		return os << t;
	}

	template<typename T, typename ... Args>
	ostream& print(ostream& os, const T& t, const Args& ... rest)
	{
		os << t << ", ";
		return print(os, rest...);
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


		int i = 0;
		double d = 3.14;
		std::string s = "how now brown cow";
		foo(i, s, 32, i);
		foo(s, 42, "hi");
		foo(d, s);
		foo("hi");

		print(std::cout, i, s, 32);

		cout << endl;
		cout << "*****************************************" << endl;
	}




	//变长函数模板实例
	template<typename...Args>
	void print_out(Args ... rest)
	{
		//非6参数偏特化版本默认assert
		assert(false);
	}

	//转化为6个参数的版本
	void print_out(int a1, int a2, int a3, int a4, int a5, int a6)
	{
		cout << a1 << ", " << a2 << ", " << a3 << "," << a4 << ", " << a5 << ", " << a6 << endl;
	}

	template<typename ... Args>
	int Vaargs(Args...rest)
	{
		int size = sizeof...(rest);
		switch (size)
		{
		case 0:
			print_out(99, 99, 99, 99, 99, 99);
			break;
		case 1:
			print_out(99, 99, rest..., 99, 99, 99);
			break;
		case 2:
			print_out(rest..., 99, 99, 99, 99);
			break;
		case 3:
			print_out(rest..., 99, 99, 99);
			break;
		default:
			print_out(0, 0, 0, 0, 0, 0);
			break;
		}
	}

	void TestChaperFive1()
	{
		Vaargs();
		Vaargs(1);
		Vaargs(1, 2);
		Vaargs(1, 2, 3);
		Vaargs(1, 2, 3, 4);
	}

}



