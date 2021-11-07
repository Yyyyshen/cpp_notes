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
//网络通信
//

//
//数据序列化就是为了在网络传输中更容易交换
//原生的SocketAPI要写一个完善的收发功能需要考虑很多细节，还需要异步等
//可以用第三方库，libcurl、cpr、ZMQ、asio
//

//
//libcurl
// 是curl的底层核心，十分稳定可靠，纯C开发，兼容和移植性好
// C++可以直接调用
//

int main()
{
	std::cout << "Hello World!\n";
	test_nlohmann_json();
}
