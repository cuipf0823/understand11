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
	}

}



