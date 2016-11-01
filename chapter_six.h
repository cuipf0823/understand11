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
}


}