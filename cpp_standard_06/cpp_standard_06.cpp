// cpp_standard_06.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <future>
#include <random>
#include <chrono>

//
//并发
//

//
//高级接口
// std::async
//  提供一个接口让一个功能在后台运行，成为一个独立线程
// std::future
//  允许等待线程结束并获取其结果
int
do_something(char c)
{
	std::default_random_engine dre(c);
	std::uniform_int_distribution<int> id(10, 1000);

	for (int i = 0; i < 10; ++i)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
		std::cout.put(c).flush();
	}

	return c;
}
int func1() { return do_something('.'); }
int func2() { return do_something('+'); }
void
test_async()
{
	//同步调用
	std::chrono::system_clock::now();
	int result_sync = func1() + func2();
	std::cout << "sync result : " << result_sync << std::endl;

	//异步调用其一
	std::future<int> result_func1(std::async(func1));		//尝试将函数立刻异步启动于一个分离线程
	int result_func2 = func2();
	int result_async = result_func1.get() + result_func2;
	//get被调用后：若启动的分离线程结束，立即得到结果；未结束则block，等待结束；未启动则启动一个同步调用，等待结果
	//所以如果get不被调用，func1是不一定会被调用的
	std::cout << "async result : " << result_async << std::endl;

	//Launch策略
	//可以强迫async绝不推延目标函数执行
	auto result = std::async(std::launch::async, func1);
	//使用策略后，不必非要调用get()，future生命结束时，等待func1结束
	//另外，如果不将async结果接住，则会产生一个临时future对象并析构，之后会阻塞到目标函数结束，相当于同步调用

	//也可以强迫一定推延执行，不执行get或wait时不会启动
	auto fu(std::async(std::launch::deferred, func1));

	//一个future只能在需要目标函数结果时调用一次，之后future处于无效状态
	//future提供另一个接口，允许等待后台操作完成而不需要处理结果，可调用一次以上
	result.wait();
	//可搭配时间段或时间点限制等待时间，wait_for/wait_until
	//返回结果是三种东西之一
	// std::future_status::deferred；async延缓操作而没有调用wait或get，表示还没有启动
	// std::future_status::timeout；操作启动了但没有在限制时间内完成
	// std::future_status::ready；操作完成
	//

	auto tp = std::chrono::system_clock::now() + std::chrono::seconds(3);
	auto f = std::async(std::launch::async, func1);
	auto status = f.wait_until(tp);
	int ret;
	if (status == std::future_status::ready)	//若没在规定时间运行完目标函数，则把另一个当结果
		ret = f.get();
	else
		ret = func2();

	//如果传入时间段是0（或者过去时间点），就可以轮询任务是否启动、运行中或完成
	//但要注意如果目标任务被推迟，可能会引发无限循环，所以进入循环之前应验证状态
	if (f.wait_for(std::chrono::seconds(0)) != std::future_status::deferred)
	{
		while (f.wait_for(std::chrono::seconds(0)) != std::future_status::ready)
		{
			//避免此线程完全占用cpu，使用yield或sleep一小段时间来提高cpu利用率
		}
	}
}
//
//等待两个Task
void
test_two_task()
{
	auto f1 = std::async(func1);
	auto f2 = std::async(func2);

	if (f1.wait_for(std::chrono::seconds(0)) != std::future_status::deferred
		|| f1.wait_for(std::chrono::seconds(0)) != std::future_status::deferred)
	{
		while (f1.wait_for(std::chrono::seconds(0)) != std::future_status::ready
			&& f1.wait_for(std::chrono::seconds(0)) != std::future_status::ready)
		{
			std::this_thread::yield();
		}
	}
	std::cout << std::endl;
	try
	{
		f1.get();
		f2.get();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}
// 
//

//
//低级接口
// thread
void
test_thread()
{
	std::thread t1(func1);//启动新线程运行func1
	t1.join();//等待func1完成

	std::thread t2(func2);
	t2.detach();//线程启动后卸离，但要注意可能main结束时该线程还在运行；进程结束时，所有线程会被直接强行终止
	//需要注意detached线程的一般处理规则
	// 线程宁可只访问local copy
	// 如果用了全局对象，应该确保这些对象在detached的线程都结束之前不要被销毁
	// 让detached线程发信号表示自己已经结束
	//
}
// 
//

//
//Mutex和Lock
// 
int g_val = 0;
std::mutex g_val_mutex;//注意生命周期问题，如果声明在局部，用和没用一样
void
test_mutex()
{
	g_val_mutex.lock();
	++g_val;
	g_val_mutex.unlock();
}
void
test_raii()
{
	//锁中间出现各类异常或提前返回都应该处理解锁，对于复杂操作，可以使用辅助对象的生命周期来控制
	std::lock_guard<std::mutex> lg_val(g_val_mutex);
	++g_val;
	//...
}
std::recursive_mutex g_re_mutex;
void
test_recursive()
{
	//嵌套锁
	/*
	std::lock_guard<std::mutex> lg(g_val_mutex);
	test_raii();//内部又一次获取锁操作，造成死锁
	*/
	//这种情况可以使用另一种锁，允许同一线程多次锁定，并在最近一次操作完成时释放lock
	std::lock_guard<std::recursive_mutex> lg(g_re_mutex);
	{
		std::lock_guard<std::recursive_mutex> lg(g_re_mutex);
		//...
	}
	std::cout << "unlock" << std::endl;
	//同时锁多个的惯用法
	std::mutex m1, m2;
	{
		std::lock(m1, m2);//同时锁两个
		//锁住之后保护起来，传递std::adopt_lock表示锁已经锁过了，只需要使用其析构时自动释放锁的特性，而不需要再执行上锁操作
		std::lock_guard<std::mutex> lg1(m1, std::adopt_lock);
		std::lock_guard<std::mutex> lg2(m2, std::adopt_lock);
	}
	//还有try_lock操作，用于尝试获取锁而不希望阻塞，自己处理其重试逻辑
}
// 
//

int main()
{
	std::cout << "Hello World!\n";
	//test_async();
	//test_two_task();
	//test_thread();
	test_recursive();
}
