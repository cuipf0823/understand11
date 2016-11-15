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
}


}