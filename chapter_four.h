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

	//C++98中 编译不通过，C++11编译通过 C++11中编译器可以智能的判断>>双括号不是右移符号
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
	//RTTI运行时类型识别，机制：每个类型产生一个type_info类型的数据，typeid就会返回，成员name用于返回类型的名字；
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
		//C++11中增加hash_code（类型的唯一哈希值），用于变量类型的比较
		White c;
		bool a_b_same = (typeid(a).hash_code() == typeid(b).hash_code());
		cout << "A and B ? " << (int)(a_b_same) << endl;
		cout << typeid(b).hash_code() << endl;

		int i;
		decltype(i) j = 0;
		cout << typeid(j).name() << endl;

	}
	//decltype使用 规则
	int i = 4;
	int arr[5] = { 0 };
	int *ptr = arr;
	struct S
	{
		double d;
	} s;
	//右值引用
	int && RvalRef();
	const bool Func(int);
	void Overloaded(int);
	void Overloaded(char);


	//decltype配合函数模板 追踪返回类型
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
		//auto关键字 类型推导
		auto name = "world\n";
		cout << "hello " << name << endl;
		int x = 1;
		int* y = &x;

		auto * a = &x; //int* 
		auto & b = x;  //int&
		auto c = y;    //int*
		auto * d = y;  //int*
		//auto * e = &foo(); //失败 指针不能指向一个临时变量
		//auto & f = foo();  //编译失败 nonconst的左值引用不能和一个临时变量绑定
		auto & g = bar();

		test_decltype();
		/*
			规则1： 单个标记符表达式以及访问类成员 推导为本类型
			*/
		decltype(arr) var1;  //int[5] 标记符表达式
		decltype(ptr) var2;  //int*
		decltype(s.d) var3;  //double
		//	decltype(Overloaded) var4; //编译失败 因为重载

		/*
			规则2：将亡值 推导为类型的右值引用
			*/
		decltype(RvalRef()) var6 = 1; //int&&
		/*
			规则3：左值，推导为类型的引用
			*/
		decltype(true ? i : i) var7 = i; //int& 三元运算符返回一个i的左值
		decltype((i)) var8 = i;          //int& 带圆括号的左值
		decltype(++i) var9 = i;
		decltype(arr[3]) var10 = i;
		decltype(*ptr) var11 = i;
		decltype("lval") var12 = "lval"; //const char(&)[9]
		/*
			规则4：以上都不是，推导为本类型
		*/
		decltype(1) var13;    //int
		decltype(i++) var14;  //int i++返回右值


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
			cout << e << endl;	 //e是解引用后的对象
		}
		cout << endl;
	}


}



