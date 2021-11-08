// LJF_cpp_notes_05.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <map>
#include <assert.h>

//技能进阶

using namespace std;

//
//序列化
//

//
//JSON
// 轻量级纯文本数据交换格式
// 
//第三方库
// boost的ptree，比较重，更严格，适用json和xml
// JSON for ModernC++，nlohmann json
#include "json.hpp"
using json_t = nlohmann::json; //定义别名，方便使用
void
test_nlohmann_json()
{
	json_t j;					//json对象
	//添加项
	j["age"] = 26;			    //"age":23
	j["name"] = "yshen";		//"name":"yshen"
	j["numbers"] = { 1,2,3 };   //"numbers":[1,2,3]
	//直接用容器填充
	map<string, int> m = { {"one",1} ,{"two",2} };
	j["kv"] = m;                //"kv":{"one":1 , "two":2}
	//序列化
	cout << j.dump(/* 2 参数指定缩进，默认为紧凑格式 */) << endl;

	//反序列化
	string str = R"({
		"name":"yshen",
		"age":26
	})";
	json_t j2;
	try {
		j2 = json_t::parse(str); //JSON数据不一定完整，格式不一定正确，可能产生异常
	}
	catch (std::exception& e) {
		cout << e.what() << endl;
	}
	assert(j2["age"] == 26);
	cout << j2["name"] << endl;
}
// 
//

//
//MessagePack
// 轻量级数据交换格式，但不是纯文本，是二进制，处理更快，Redis就是用此格式
// 和nlohmann json一样是head only
// 没有定义数据结构，只对基本类型和标准容器序列化、反序列化
// vector<int> v = {1,2,3,4,5};
// msgpack::sbuffer sbuf;
// msgpack::pack(sbuf, v);
// 是一个缓冲区，和vector<char>很像
// auto handle = msgpack::unpack(sbuf.data(),sbuf.size()); 反序列化
// auto obj = handle.get(); 得到对象
// vector<int> v2;
// obj.convert(v2); 转换数据
//

//
//ProtoBuffer
// google出品的pb，也是二进制，库更重一些
// 需要预先定义好数据结构，写一个IDL，定义数据模式
// （lua里用过）
//

//
//boost::archive
// 之前项目里用过，在需要序列化的类型里加上一个
// void serialize(Archive& ar, const unsigned int version)
// 定义好序列化的成员
// 感觉用起来也很轻便
//


//
//网络通信
//

//
//数据序列化就是为了在网络传输中更容易交换
//原生的SocketAPI要写一个完善的收发功能需要考虑很多细节，还需要异步等
//可以用第三方库，libcurl、cpr、ZMQ、asio、beast
//

//
//libcurl
// 是curl的底层核心，十分稳定可靠，纯C开发，兼容和移植性好
// C++可以直接调用
#include <curl/curl.h>
size_t write_callback(char*, size_t, size_t, void*);//回调函数原型
void
test_curl() {
	auto curl = curl_easy_init();//创建CURL句柄
	assert(curl);

	curl_easy_setopt(curl, CURLOPT_URL, "http://nginx.org");//设置各种参数
	//...没设置回调函数的话，默认使用内部回调，把响应内容输出到标准流，也就是直接打印
	//curl是纯C写的，所以回调需要是函数指针，C++中lambda更方便，就又一个特别的转换技巧
	//无捕获（[]内为空）的lambda表达式可以显式转换成函数指针，定义一个函数原型后，可以做如下转换后调用
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
		(decltype(&write_callback)) //回调函数原型指针类型，显式进行转换
		[](char* ptr, size_t size, size_t nmemb, void* userdata) {
			cout << std::string(ptr) << endl;
			cout << "size:" << size * nmemb << endl;
			return size * nmemb;
		});
	//主要使用就是各种opt的设置，可以封装一个类来使用

	auto res = curl_easy_perform(curl);//执行
	if (res != CURLE_OK)//检查执行结果
		cout << curl_easy_strerror(res) << endl;

	curl_easy_cleanup(curl);//清理句柄
}
// 
//

//
//cpr
// 是对curl的一个C++11封装，接口更加易用
// https://docs.libcpr.org/
//

//
//ZMQ
// 不仅是网络库，更像一个异步并发框架（未支持win10）
// 除了支持tcp/ip，还支持进程内和进程间通信
//

//C++23，预计加入networking，基于boost.asio，前摄器模式统一封装了操作系统的各种异步机制（epoll、kqueue、IOCP），支持协程


//
//C++为底层基础，脚本语言作为上层建筑的混合系统
//

//
//python有C接口，可以写扩展模块，但比较麻烦，可以用C++中的一些特性简化工作
// https://github.com/pybind/pybind11
// 用C++开发python扩展，借鉴了boost.python
//

//
//lua
// 游戏常用脚本语言，使用解释器运行，速度很快
// LuaJIT用了JIT技术，把lua即时编译成机器码，速度几乎和C/C++媲美
// https://github.com/openresty/luajit2 （第三方luajit分支，比官方维护快）
// 
//与C++交互
// LuaBridge，需要把C++接口转成C接口导出
//


//
//性能分析
//

//
//系统级工具
// Linux
//	top、sar、vmstat、netstat等
// 
// top
//	最简单直观查看CPU，内存等关键性能指标
// pstack
//	查看进程调用栈信息，是进程的静态截面
// strace
//	可以显式进程正在运行的系统调用，是实时的
// 
// 三个信息结合看，基本能知道进程在干什么，分析出瓶颈
// perf
//	按固定频率采样，相当于连续多次执行pstack，然后统计函数调用次数，算出百分比
//	采样频率足够大时，把所有静态截面组合，就能得到可信数据，全面描述CPU情况
//	perf top -K -p xxx
//	按CPU使用率排序，只看用户空间的调用，容易找出最消耗CPU的函数
//	通常可以快速定位系统瓶颈，找到优化方向
// 
//源码级工具
// 侵入式分析工具，在源码里埋点（计时器、计数器、日志打印其实都算）
// Google Performance Tools， gperftools，一个C++工具集
// 分析工具有CPUProfiler和HeapProfiler（使用智能指针和标准容器基本可以忽略）
// CPUProfiler原理和perf差不多
//auto make_cpu_profiler =            // lambda表达式启动性能分析
//[](const string& filename)          // 传入性能分析的数据文件名
//{
//	ProfilerStart(filename.c_str());  // 启动性能分析
//	ProfilerRegisterThread();         // 对线程做性能分析
//
//	return std::shared_ptr<void>(     // 返回智能指针
//		nullptr,                        // 空指针，只用来占位
//		[](void*) {                      // 删除函数执行停止动作
//			ProfilerStop();             // 停止性能分析
//		}
//	);
//};
void test_something()
{
	//auto cp = make_cpu_profiler("case1.perf");

	//do something

	//析构时自动调用停止性能分析函数
}
// *.perf文件是二进制的，需要pprof工具输出文本形式的分析报告
// pprof --text ./a.out case1.perf > case1.txt
// 报告格式与perf很像，源码级的采样很详细，但大量内部函数细节很难找重点
// 也可输出图形化报告
// https://github.com/gperftools/gperftools/tree/master/docs
//

int main()
{
	std::cout << "Hello World!\n";
	//test_nlohmann_json();
	test_curl();
}
