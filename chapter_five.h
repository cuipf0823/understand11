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
#include <stdlib.h>
#include <list>
#include <deque>
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

	void TestChaperFive2();

	void TestChaperFive1()
	{
		Vaargs();
		Vaargs(1);
		Vaargs(1, 2);
		Vaargs(1, 2, 3);
		Vaargs(1, 2, 3, 4);
		typedef int* INTPTR;
		INTPTR a = new int(8);
		cout << *a << endl;

		TestChaperFive2();
	}

	template <typename T>
	class TestTraits
	{
	public:
		typedef	T value_type;     //内嵌类型声明
		TestTraits(T* p = nullptr) : ptr(p)
		{

		}
		T& operator*() const
		{
			return *ptr;
		}
	private:
		T* ptr;
	};

	template<typename T>
	typename T::value_type func(T it)
	{
		return *it;
	}

	class TestNew
	{
	public:
		TestNew(int b)
		{
			a = b;
			cout << "construct" << endl;
		}
	private:
		int a;
	};

	template<typename...Args>
	void Out(int n, Args&&... args)
	{
		cout << n << endl;
	}
	template<typename...Args>
	void Emplace(Args&&... args)
	{
		Out(sizeof...(args), std::forward<Args>(args)...);
	}

	//模板
	template <typename Tp, typename Ref, typename Ptr>
	struct TestOp
	{
		typedef size_t difference_type;
		TestOp()
		{
			cur = nullptr;
		}
		Tp* cur;
		
		inline bool operator==(const TestOp& __y)
		{
			cout << "inside operator1" << endl;
			return this->cur == __y.cur;
		}

		template<typename _Tp, typename _RefR, typename _PtrR>
		inline bool operator==(const TestOp<_Tp, _RefR, _PtrR>& __y)
		{
			cout << "inside operator2" << endl;
			return this->cur == __y.cur;
		}
		
	};
	template<typename _Tp, typename _Ref, typename _Ptr>
	inline bool operator==(const TestOp<_Tp, _Ref, _Ptr>& x, const TestOp<_Tp, _Ref, _Ptr>& y)
	{
		cout << "outside operator1" << endl;
		return x.cur == y.cur;
	}

	template<typename _Tp, typename _RefL, typename _PtrL, typename _RefR, typename _PtrR>
	inline bool operator==(const TestOp<_Tp, _RefL, _PtrL>& x, const TestOp<_Tp, _RefR, _PtrR>& y)
	{
		cout << "outside operator2" << endl;
		return true;
	}
	//返回值前面的typename不能省去
	template<typename _Tp, typename _RefL, typename _PtrL, typename _RefR, typename _PtrR>
	inline typename TestOp<_Tp, _RefL, _PtrL>::difference_type operator-(const TestOp<_Tp, _RefL, _PtrL>& x, const TestOp<_Tp, _RefR, _PtrR>& y)
	{
		cout << "outside operator -" << endl;
		return x.cur == y.cur;
	}

	void TestChaperFive2()
	{
		TestTraits<int> ite(new int(8));
		cout << func(ite) << endl;
		int att = 10;
		TestTraits<int*> pte(new (int*)(&att));
		cout << func(pte) << endl;

		TestTraits<int*>::value_type ac;

		//关于右值
		int rr0 = 34;
		int &&rr1 = 42;
		int &rr2 = rr0;
		int &&rr3 = std::move(rr2);
		cout << rr2 << endl;

		//关于new的使用
		//1. 申请空间 调用构造函数
		TestNew* p_new = new TestNew(9);

		//2.仅仅赋值用，调用构造函数 
		void* p_new1 = malloc(sizeof(TestNew));
		::new (static_cast<void*>(p_new1)) TestNew(100);
		free(p_new1);
		
		//3.仅仅用于申请空间
		TestNew* start_free = static_cast<TestNew*>(::operator new(100));
		delete start_free;

		cout << size_t(-1) / sizeof(char) << endl;
		cout << size_t(-1) << endl;

		union Obj
		{
			union Obj* next;
			char data[1];
		};
		cout << sizeof(Obj) << endl;

		Emplace(1, 2, 2, 2, 4, 4, 6);

		std::vector<int> ivect = { 1, 2, 3, 3, 67 };
		cout << ivect.max_size() << endl;
		cout << sizeof(nullptr) << endl;
		cout << sizeof(nullptr_t) << endl;				
		nullptr_t my_null;
		cout << &my_null << endl;

		//lambda
		int girls = 2;
		int boys = 3;
		auto totalChild = [](int x, int y) -> int{ return x + y; };
		cout << totalChild(girls, boys) << endl;
		//最简单的lambda函数
		[]{};
		auto totalChild1 = [girls, &boys]() ->int{return girls + boys; };
		cout << totalChild1() << endl;

		//仿函数
		struct Functor
		{
			int operator()(int x, int y)
			{
				return x + y;
			}
		};
		Functor total;
		cout << total(boys, girls) << endl;

		int tx = 3;
		int ty = 4;
		float a = 4.0;
		float b = 4.0;
		int success = 0;
		auto valid1 = [&]() -> bool
		{
			if (tx + ty > boys)
			{
				return true;
			}
			else
			{
				return false;
			}
		};

		std::list<int> ilist = { 1, 2, 3, 5 };
		std::list<int>::iterator iter = ilist.end();
		if (++iter == ilist.begin())
		{
			cout << "1111" << endl;
		}

		TestOp<int, int&, int*> it, it0;
		TestOp<int, unsigned int&, unsigned int*> uit;
		if (it == uit)
		{
			cout << "it == uit" << endl;
		}
		if (it == it0)
		{
			cout << "it == it0" << endl;
		}
	}

}



