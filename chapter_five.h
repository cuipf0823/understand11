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
	//C++11�� ǿ����ö��  
	enum class Type: char
	{
		General = 1,
		Light,
		Medium,
		Heavy
	};

	//����ʱ����
	constexpr int GetConst()
	{
		return 1;
	}

	const int GetRunConst()
	{
		return 1;
	}

	//�������ʽ����Ҫ��������ֻ��һ����� data�����޷�ͨ������
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



	//�䳤����ģ��
	template<int...A>
	class NonTypeTemplate
	{

	};
	//ʵ����
	NonTypeTemplate<1, 0, 3> vint;

	//Args��һ��ģ���������ʾ0�����߶��ģ�����Ͳ���
	//rest���������� ��ʾ0�����߶����������
	template <typename T, typename... Args>
	void foo(const T& t, const Args& ... rest)
	{
		std::cout << sizeof ...(Args) << endl;	  //�������͵���Ŀ
		std::cout << sizeof ...(rest) << endl;	  //������������Ŀ
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
//		t = General;   //���벻ͨ�� ����ʹ��ǿ��������

		//C++11����ָ���ʹ��
		unique_ptr<int> up1(new int(11)); //�޷����Ƶ�unique_ptr
//		unique_ptr<int> up2 = up1;        //����ͨ������
		unique_ptr<int> up3 = move(up1);  //Ŀǰup3 ������Ψһ������ָ��
		cout << *up3 << endl;
		/*
		����ʱ����
		cout << *up1 << endl;
		*/
		up3.reset();

		//�������ʹ�ñ��볣�����������г������벻ͨ��
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




	//�䳤����ģ��ʵ��
	template<typename...Args>
	void print_out(Args ... rest)
	{
		//��6����ƫ�ػ��汾Ĭ��assert
		assert(false);
	}

	//ת��Ϊ6�������İ汾
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



