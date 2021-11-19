// cpp_standard_03.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <tuple>
#include <vector>

//
//通用工具
//

//
//Pair/Tuple
// 可以将两个（多个）不同类型value视为一个单元而不需要特别定义class
// map系列容器就使用了pair作为元素
void
test_pair()
{
	//由于pair是struct定义的，所有成员都是public
	std::pair<int, std::string> p1;
	std::cout << p1.first << ":" << p1.second << std::endl;
	//可以对pair使用tuple-like接口
	std::get<0>(p1);//p.first
	std::get<1>(p1);//p.second
	std::tuple_element<0, decltype(p1)>::type; //int
	//无需写出类型的方式生成对象
	auto p2 = std::make_pair(42, 42.0);//<int,double>
	//比较机制，所有元素都相等；第一个元素优先级更高
}
void
test_tuple()
{
	//使用和pair差不多，只是能容纳更多类型元素
	//tuple元素类型可以是reference
	//建立tuple两个方式
	std::make_tuple(42, 4.2, "hello");//值形式
	int i;
	double d;
	std::string str;
	std::tie(i, d, str);//以reference建立tuple
	//相当于
	std::make_tuple(std::ref(i), std::ref(d), std::ref(str));
	//可以用pair作为初值初始化一个双元素tuple
}
//

//
//Smart Pointer
// shared_ptr
void
test_shared_ptr()
{
	//两种方式构造
	auto p_str1 = std::make_shared<std::string>("hello");
	std::shared_ptr<std::string> p_str2(new std::string("world"),
		[](std::string* p) {
			std::cout << "delete " << *p << std::endl;
			delete p;
		});
	//容器存放智能指针
	std::vector<std::shared_ptr<std::string>> vec_sp;
	vec_sp.push_back(p_str1);
	vec_sp.push_back(p_str1);
	vec_sp.push_back(p_str2);
	vec_sp.push_back(p_str1);
	vec_sp.push_back(p_str2);
	for (auto p : vec_sp)
		std::cout << *p << " ";
	std::cout << std::endl;
	std::cout << "hello use_count() : " << vec_sp[0].use_count() << std::endl;
	std::cout << "world use_count() : " << vec_sp[2].use_count() << std::endl;
	//针对数组，由于shared_ptr默认是拥有new建立的单一对象，需要自己定义deleter
	std::shared_ptr<int> p_int_arr(new int[10],
		[](int* p) {
			delete[] p;
		});
	//或者使用unique_ptr提供的辅助函数
	std::shared_ptr<int> p_int_arr2(new int[10],
		std::default_delete<int[]>());
	//unique_ptr是可以声明数组为template
	std::unique_ptr<int[]> up_int_arr(new int[10]);	//是OK的

	//当两个shared_ptr因某些情况下互相指向了对方，出现了环式指向，即使离开作用域，两个对象use_count仍是1，不会被释放
	//或者某个对象需要共享但不愿持有时，有一个weak_ptr
	//它接受一个shared_ptr，当其他持有其指向对象得pointer失去拥有权时，weak_ptr会自动成空
	//不能使用*和->访问所指对象，因为性质上它是一个寿命大于所指对象的引用，不能保证对象有效
	//一般只用于创建、复制、赋值，转换为一个shared pointer，或检查自己是否指向一个对象

	std::shared_ptr<std::string> sp_str(new std::string("hello"));
	std::weak_ptr<std::string> wp = sp_str;
	sp_str.reset();
	std::cout << wp.use_count() << std::endl;//0
	std::cout << std::boolalpha << wp.expired() << std::endl;//true
	std::shared_ptr<std::string> sp_str2(wp);//throw std::bad_weak_ptr

	//shared_ptr误用情况
	int* p_int = new int;
	std::shared_ptr<int> sp1(p_int);
	std::shared_ptr<int> sp2(p_int);//应当保证某对象只被一组shared_ptr拥有；ERROR
	//sp1,sp2都会在丢失p拥有权时释放资源（double free）
	//如果真的想拥有该资源，应该做如下操作
	std::shared_ptr<int> sp3(sp1);
	//有时可能间接引起这种情况，如在类中通过this建立shared_ptr，相当于一个新的拥有者
	//可以把这种需要建立智能指针的类声明为继承于std::enable_shared_from_this<>
	//再需要以this建立sp时，可以直接使用shared_from_this()。（在之前boost asio中经常这样用）

}
// 
//

//
//数值极值
// numeric_limits
// 利用这个实现平台无关的代码
//

//
//type trait/utility
// 检验类型
// std::ref 隐式转换为T&
// std::function 
//

//
//辅助函数
// min/max，可自定义比较函数
// swap交换
// ratio 编译期分数运算
//
// clock、timer
#include <chrono>
void
test_chrono()
{
	//duration 时间段
	std::chrono::duration<int> twenty_sec(20);//默认“分数”以秒记单位
	std::chrono::duration<double, std::ratio<60>> half_min(0.5);
	std::chrono::duration<long, std::ratio<1, 1000>> one_mill_sec(1);//毫秒ms
	//但有些麻烦，标准库定义了一些常用单位
	std::chrono::seconds twenty_sec2(20);
	std::chrono::hours one_day(24);
	std::chrono::microseconds one_micro_sec(1);//微秒（nano纳秒）

	//clock和timepoint
	auto tp_now = std::chrono::system_clock::now();//程序执行到现在的开始时间；返回类型是time_point

}
//
//<cstddef> 
// nullptr_t,size_t,ptrdiff_t(指针间距离)
// 
//<cstdlib>
// exit(),abort()
//  
//<cstring>
// memchr,memcmp,memcpy,memmove,memset
// 
//

int main()
{
	std::cout << "Hello World!\n";
	test_shared_ptr();
}
