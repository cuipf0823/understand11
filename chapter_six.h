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
#include <boost/smart_ptr.hpp>
#include <unordered_map>


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


//测试unordered_map相关操作
typedef std::unordered_map<int, int> HashMap;
HashMap info_hash_map;
std::map<int, int> info_map;
void test_hash_map()
{
	for (int idx = 0; idx < 10; ++idx)
	{
		info_hash_map[idx] = idx;
		info_map[idx] = idx;
	}

	auto iter = info_hash_map.find(9);
	auto iter_map = info_map.find(5);
	if (iter != info_hash_map.end() && iter_map != info_map.end())
	{
		cout << iter->first << "------" << iter->second << endl;
		cout << iter_map->first << "------" << iter_map->second << endl;
	}

	for (int i = 20; i < 10000; ++i)
	{
		info_hash_map[i] = i;
		info_map[i] = i;
	}

	if (iter != info_hash_map.end() && iter_map != info_map.end())
	{
		cout << iter->first << "------" << iter->second << endl;
		cout << iter_map->first << "------" << iter_map->second << endl;
	}
}

struct MutexInfo;
typedef std::list<MutexInfo> MutexInfoList;
typedef std::unordered_map<uint32_t, MutexInfoList::iterator> MutexPair;
typedef std::unordered_map<uint32_t, MutexPair> MutexTuple;
struct MutexInfo 
{
	uint32_t scene_id;
	uint32_t mutex_id;
	uint32_t uid;
	MutexTuple::iterator iter1;
	MutexTuple::iterator iter2;
};

//user scene iterator
MutexTuple user_scene_;
//scene mutex iterator
MutexTuple scene_mutex_;

MutexInfoList mutexs_;

void test_mutex()
{
	//init 知道 uid scene_id, mutex_id
	uint32_t uid = 100999;
	uint32_t scene_id = 2;
	uint32_t mutex_id = 1;
	MutexInfo info;
	info.uid = uid;
	info.scene_id = scene_id;
	info.mutex_id = mutex_id;
	mutexs_.push_front(info);
	
	MutexInfoList::iterator iter = mutexs_.begin();

	MutexPair scene_pair = { {scene_id, iter} };
	user_scene_[uid] = scene_pair;

	MutexPair mutex_pair = { { mutex_id, iter } };
	scene_mutex_[scene_id] = mutex_pair;
	iter->iter1 = user_scene_.begin();
	iter->iter2 = scene_mutex_.begin();


	//插入第二个元素
	info.mutex_id = mutex_id + 100;
	info.scene_id = scene_id + 100;
	info.uid = uid + 100;
	mutexs_.push_front(info);
	iter = mutexs_.begin();

	scene_pair.clear();
	mutex_pair.clear();
	scene_pair = { { info.scene_id, iter } };
	mutex_pair = { { info.mutex_id, iter } };
	user_scene_[info.uid] = scene_pair;
	scene_mutex_[info.scene_id] = mutex_pair;
	iter->iter2 = scene_mutex_.find(info.scene_id);
	iter->iter1 = user_scene_.find(info.uid);

	cout << " user_scene_: " << endl;
	for (auto& aiter : user_scene_)
	{
		MutexPair& mutex_pair = aiter.second;
		cout << "first: " << aiter.first << " second: " << mutex_pair.begin()->first << endl;
		MutexInfoList::iterator list_iter = mutex_pair.begin()->second;
		cout << "mutex_id: " << list_iter->mutex_id << endl;
	}

	//删除元素
	MutexTuple::iterator it = user_scene_.find(uid);
	auto list_iter = it->second.begin()->second;
	user_scene_.erase(list_iter->iter1);
	scene_mutex_.erase(list_iter->iter2);
	mutexs_.erase(list_iter);

	cout << " after del user_scene_: " << endl;
	for (auto& aiter : user_scene_)
	{
		MutexPair& mutex_pair = aiter.second;
		cout << "first: " << aiter.first << " second: " << mutex_pair.begin()->first << endl;
		MutexInfoList::iterator list_iter = mutex_pair.begin()->second;
		cout << "mutex_id: " << list_iter->mutex_id << endl;
	}

	cout << "mutexs list: " << mutexs_.size() << endl; 


	std::map<uint32_t, uint32_t> test_maps;
	for (int idx = 0; idx < 15; ++idx)
	{
		test_maps[idx] = idx;
	}

	for (auto& it : test_maps)
	{
		if (it.first % 2 ==0)
		{
			auto iter = test_maps.find(it.first);
			if (iter != test_maps.end())
			{
				test_maps.erase(iter);
			}
			cout << "test maps : " << it.first << " " << it.second << endl;
		}
	}
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

	/*
		tuple的使用
	*/

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
	//使用tuple返回多个值 tuple常见用途之一

	//定义编译时期的常量
	std::cout << "integal_constant: " << std::integral_constant<int, 5>::value << std::endl;
	using one_type = std::integral_constant < int, 10 > ;
	std::cout << one_type::value << endl;
	struct OneType : std::integral_constant < int, 100 >
	{

	};
	std::cout << OneType::value << endl;
	//编译时期的true 和 false
	using true_type = std::integral_constant < bool, true > ;
	using false_type = std::integral_constant < bool, false > ;
	std::cout << true_type::value << " " << false_type::value << endl;

	using type1 = std::conditional<true, int, double>::type;
	using type2 = std::conditional<false, int, double>::type;
	std::cout << typeid(type1).name() << std::endl;
	std::cout << typeid(type2).name() << std::endl;
	std::cout << typeid(std::conditional<OneType::value >= one_type::value, float, int>::type).name() << endl;

	typedef boost::shared_ptr<int> IntPtr;
	std::set<IntPtr> b_sets;
	IntPtr b_n(new int(10));
	std::cout << b_n.use_count() << endl;
	IntPtr b_n1(b_n);
	std::cout << b_n1.use_count() << endl;
	std::cout << b_n.use_count() << endl;
	const IntPtr& b_n2 = b_n;
	std::cout << b_n1.use_count() << endl;
	std::cout << b_n.use_count() << endl;
	b_sets.insert(b_n);
	b_n1.reset();
	std::cout << "____________________________" << endl;
	std::cout << b_n.use_count() << endl;
	std::cout << b_n1.use_count() << endl;
	std::cout << b_n2.use_count() << endl;
	b_n.reset();
	std::cout << "____________________________" << endl;
	std::cout << b_n.use_count() << endl;
	std::cout << b_n1.use_count() << endl;
	std::cout << b_n2.use_count() << endl;
	//std::cout << b_sets.begin()->unique() << endl;
	std::cout << b_sets.begin()->use_count() << endl;


	test_hash_map();
	test_mutex();

}
}