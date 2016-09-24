#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <type_traits>
#include <vector>
#include <map>
#include <typeinfo>
#include <initializer_list>
using namespace std;
namespace Four
{

	//C++98�� ���벻ͨ����C++11����ͨ�� C++11�б������������ܵ��ж�>>˫���Ų������Ʒ���
	std::vector<int> int_vec;
	const vector<int> v = static_cast<const vector<int>>(int_vec);

	double foo()
	{
		double tmp = 0;
		return tmp;
	}
	std::vector<int>& bar()
	{
		return int_vec;
	}

	//decltype
	//RTTI����ʱ����ʶ�𣬻��ƣ�ÿ�����Ͳ���һ��type_info���͵����ݣ�typeid�ͻ᷵�أ���Աname���ڷ������͵����֣�
	class White {};
	class Black {};
	template<typename T1, typename T2>
	void Sum(T1& t1, T2& t2, decltype(t1 + t2) & s)
	{
		s = t1 + t2;
	}

	void test_decltype()
	{
		White a;
		Black b;
		cout << typeid(a).name() << endl;
		cout << typeid(b).name() << endl;
		//C++11������hash_code�����͵�Ψһ��ϣֵ�������ڱ������͵ıȽ�
		White c;
		bool a_b_same = (typeid(a).hash_code() == typeid(b).hash_code());
		cout << "A and B ? " << (int)(a_b_same) << endl;
		cout << typeid(b).hash_code() << endl;

		int i;
		decltype(i) j = 0;
		cout << typeid(j).name() << endl;

	}
	//decltypeʹ�� ����
	int i = 4;
	int arr[5] = { 0 };
	int *ptr = arr;
	struct S
	{
		double d;
	} s;
	//��ֵ����
	int && RvalRef();
	const bool Func(int);
	void Overloaded(int);
	void Overloaded(char);


	//decltype��Ϻ���ģ�� ׷�ٷ�������
	template<typename T1, typename T2>
	auto TemSum(const T1& t1, const T2& t2) -> decltype(t1 + t2)
	{
		return t1 + t2;
	}

	template<typename T1, typename T2>
	auto Mul(const T1& t1, const T2& t2) -> decltype(t1 * t2)
	{
		return t1 * t2;
	}

	int ReturnFunc(int i, int j)
	{
		return i + j;
	}

	void TestChaperFour()
	{
		//auto�ؼ��� �����Ƶ�
		auto name = "world\n";
		cout << "hello " << name << endl;
		int x = 1;
		int* y = &x;

		auto * a = &x; //int* 
		auto & b = x;  //int&
		auto c = y;    //int*
		auto * d = y;  //int*
		//auto * e = &foo(); //ʧ�� ָ�벻��ָ��һ����ʱ����
		//auto & f = foo();  //����ʧ�� nonconst����ֵ���ò��ܺ�һ����ʱ������
		auto & g = bar();

		test_decltype();
		/*
			����1�� ������Ƿ����ʽ�Լ��������Ա �Ƶ�Ϊ������
			*/
		decltype(arr) var1;  //int[5] ��Ƿ����ʽ
		decltype(ptr) var2;  //int*
		decltype(s.d) var3;  //double
		//	decltype(Overloaded) var4; //����ʧ�� ��Ϊ����

		/*
			����2������ֵ �Ƶ�Ϊ���͵���ֵ����
			*/
		decltype(RvalRef()) var6 = 1; //int&&
		/*
			����3����ֵ���Ƶ�Ϊ���͵�����
			*/
		decltype(true ? i : i) var7 = i; //int& ��Ԫ���������һ��i����ֵ
		decltype((i)) var8 = i;          //int& ��Բ���ŵ���ֵ
		decltype(++i) var9 = i;
		decltype(arr[3]) var10 = i;
		decltype(*ptr) var11 = i;
		decltype("lval") var12 = "lval"; //const char(&)[9]
		/*
			����4�����϶����ǣ��Ƶ�Ϊ������
		*/
		decltype(1) var13;    //int
		decltype(i++) var14;  //int i++������ֵ


		auto w = 3;
		auto xu = 4L;
		auto pi = 3.14;
		auto sb = TemSum(w, xu);
		cout << is_const<decltype(sb)>::value << endl;
		cout << is_rvalue_reference<decltype(sb)>::value << endl;
		cout << is_lvalue_reference<decltype(TemSum(w, xu))>::value << endl;
		auto u = Mul(TemSum(w, xu), pi);
		cout << u << endl;


		const long int& test_value = TemSum(w, xu);
		const int& total = ReturnFunc(1, 2);

		int array[5] = { 1, 2, 3, 4, 5 };
		for (const auto& e : array)
		{
			cout << e << "\t";
		}
		cout << endl;

		vector<unsigned int> vec_for = { 11, 22, 33, 4 };
		for (auto i = vec_for.begin(); i != vec_for.end(); ++i)
		{
			cout << dec << *i << "\t";
		}
		cout << endl;

		for (const auto& e : vec_for)
		{
			cout << e << endl;	 //e�ǽ����ú�Ķ���
		}
		cout << endl;
	}


}



