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
#include <queue>
#include <string.h>
#include <set>
#include <tuple>


namespace Six
{

template<typename T>
void print_queue(T& q)
{
	while (!q.empty())
	{
		std::cout << q.top() << " ";
		q.pop();
	}
	std::cout << endl;
}

typedef int* int_ptr;
int_ptr g_var = new int(100);
int_ptr g_var2 = new int(900);
int_ptr g_var3 = g_var;

int_ptr& GetIntPtr()
{
	return g_var;
}

int_ptr& GetIntPtr2()
{
	return g_var2;
}

void PrintIntIntSet(std::set<int>& m, const char* pre) 
{
	std::set<int>::iterator it;
	std::cout << pre;
	for (it = m.begin(); it != m.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

template<typename T>
T&& TestIdentity(T&& t)
{
	return std::forward<T>(t);
}

void TestChaperSix()
{
	std::priority_queue<int> iq;
	for (auto n : {12, 2, 3, 56, 78})
	{
		iq.push(n);
	}
	print_queue(iq);
	std::priority_queue<int, std::vector<int>, std::greater<int>> q2;
	for (auto n : { 12, 22, 23, 256, 278 })
	{
		q2.push(n);
	}
	print_queue(q2);

	auto cmp = [](int left, int right)
	{
		return (left ^ 1) < (right ^ 1);
	};
	std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(cmp);
	for (auto n : { 12, 22, 23, 256, 278 })
	{
		q3.push(n);
	}
	print_queue(q3);


	//指向整型指针的指针
	int a[5] = { 1, 2, 3, 4, 5 };
	int *p = a;  //等效于 int *p = &a[0]
	int** point = &p;
	assert(*point == p);
	assert(**point == a[0]);
	**point = 20;//right
	
	int* old = *point;
	cout << old << endl;
	cout << &a[0] << endl;
	cout << a << endl;
	cout << "********************************" << endl;


	const int kMaxLen = 4;
	int** ipoint = new int*[kMaxLen];
	memset(ipoint, 0, sizeof(ipoint[0]) * kMaxLen);
	for (int i = 0; i < kMaxLen; ++i)
	{
		int** p = &ipoint[i];
		*p = &i;
		cout << "i = " << i << "  "<< *p << endl;
	}

	int** cp = &ipoint[0];
	int* cold = *cp;
	cout << &cp << endl;
	cout << *cp << endl;
	cout << cold << endl;
	cout << *((*cp)++) << endl;

	std::hash<std::string> h;
	cout << h("dkkdlkld") << endl;

	cout << *g_var << endl;
	int_ptr var = new int(1520);
	GetIntPtr() = GetIntPtr2();
	cout << *g_var << endl;
	
	
	delete g_var3;
	delete g_var2;
	delete var;



	std::map<char, int> mymap;

	mymap['a'] = 10;
	mymap['b'] = 20;
	mymap['f'] = 100;
	mymap['c'] = 30;

	//std::pair<std::map<char, int>::iterator, std::map<char, int>::iterator> ret;
	auto ret = mymap.equal_range('b');

	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';

	std::cout << "upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';

	std::string x ;
	bool comp = true;
	x = (comp ? "11111" : "22222");
	std::cout << x << std::endl;

	std::set<int> iset;
	iset.emplace(1);
	iset.emplace(100);
	iset.emplace(2);
	iset.emplace(34);
	PrintIntIntSet(iset, "iset:");
	auto iret = iset.emplace(2);
	if (!iret.second)
	{
		std::cout << "aready exist" << endl;
	}
	std::string str("66666");
	std::string& str_lref = str;
	std::string&& str_rref = std::move(str_lref);  //使用时候依然是 左值
	std::string&& str_rref1 = std::move(str);
	std::string&& str_rref2 = static_cast<std::string&&>(str); //等价于使用std::move
	
	std::string&& str2 = TestIdentity<std::string>(std::move(str));	 //T： string	传参数：右值引用	返回：右值引用
	std::string& str3 = TestIdentity<std::string&>(str_lref);        //T:  string& 	传参数：左值引用（引用折叠）返回：左值引用
	std::string&& str4 = TestIdentity<std::string&&>(std::move(str));//T:  string&&  传参数：右值引用 返回：右值引用 
	std::string& str5 = TestIdentity(str4);							 //T:  string&  传参数：左值引用 返回：左值引用


	//tuple的初始化
	std::tuple<size_t, size_t, size_t> threeD; 
	std::tuple<std::string, std::vector<double>, int, std::list<int>> someVal("constants", { 3.14, 2.78 }, 42, { 1, 2, 3, 4 });
	//此时 item为 tuple<const char*, int, double>
	auto item = std::make_tuple("0-999-123-x", 2, 20.12);

	//成员tuple成员访问
	auto book = std::get<0>(item);
	auto cnt = std::get<1>(item);
	auto price = std::get<2>(item);
	std::cout << "book: " << book << " cnt: " << cnt << " price: " << price << std::endl;
	//auto form = std::get<3>(item);

	typedef decltype(item) Trans; //Trans 是item的类型；
	//返回Trans类型对象中成员的数量
	std::cout << std::tuple_size<Trans>::value << endl;
	//获取类型 cnt类型与item中第二个成员相同
	std::tuple_element<1, Trans>::type cnt_type = std::get<1>(item);

	//使用tuple返回多个值
}



}