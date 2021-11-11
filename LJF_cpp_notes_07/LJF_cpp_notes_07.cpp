// LJF_cpp_notes_07.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//应用实践

//本例总结
// 
//项目起始阶段 认真做需求分析，应用设计模式和原则，得出灵活可扩展的面向对象系统
//C++ 项目里最好有核心头文件，集中定义所有标准头、语言特性、宏定义等，规范使用，搭好架构
//原子变量实现自旋锁，比互斥量成本低，更高效
//使用ZMQ简化网络通信，注意异常处理
//使用Lua脚本语言进行混合开发
//理解、用好C++特性，适当使用final、default、const等关键字，代码更安全，可读性高，利于维护
//

//惯用代码规范
// 
//空行分隔逻辑段落
//类名用CamelCase，函数和变量用snake_case，根据变量类型添加前缀，如成员变量用 m_
//在编译阶段使用静态断言，保证整数、浮点数精度
//不需要继承的类使用final，禁止外界产生子类
//使用default显式定义拷贝构造、拷贝赋值、转移构造、转移赋值等重要函数（尤其需要存入容器的对象类型，填入容器时会拷贝，显式声明转移函数可以节约很多性能）
//使用委托构造编写多个不同形式的构造
//成员变量在声明时直接初始化
//using定义类型别名，调整时减少修改
//适当使用const修饰常函数
//明确知道不抛异常的函数标记为noexcept进行优化
//

//=======================================================================

//
//书店应用（C++ Primer中例子参考）
//

//
//项目功能
// 销售记录管理
// 多渠道获取书号、销售册数、销售额
// 简单统计分析
// 数据定期上报
//

//定义完各类，进行组合
#include "cpplang.hpp"							//核心头文件

#include "Config.hpp"							//封装配置文件，混合lua脚本
#include "Summary.hpp"							//数据汇总处理
#include "Zmq.hpp"								//网络通信

#include "json.hpp"								//上报用json
//#include <cpr/cpr.h>							//curl封装

USING_NAMESPACE(yyyyshen);
USING_NAMESPACE(std);

int main()
try {											//try/catch function形式，将整个main包起来
	std::cout << "Server Start" << std::endl;

	Config conf;
	conf.load("./conf.lua");					//读取lua配置文件

	Summary sum;
	std::atomic_int count{ 0 };					//数据存储和统计

	auto recv_cycle = [&]()						//服务器主循环lambda函数，引用模式捕获上面变量
	{											//主业务：ZMQ接收数据、msgpack反序列化、存储数据；主循环只接收数据，包装后扔到另外的线程取处理

		using zmq_ctx = ZmqContext<1>;
		auto sock = zmq_ctx::recv_sock();		//获取zmq的接收sock，并根据配置绑定接收端口
		sock.bind(conf.get<string>("config.zmq_ipc_addr"));
		assert(sock.handle() != nullptr);

		for (;;)								//服务器无限循环运行
		{
			auto msg_ptr =						//把即将获取的数据包封装进智能指针
				std::make_shared<zmq_message_type>();
			sock.recv(*msg_ptr.get());			//接收数据，阻塞模式

			++count;							//计数

			std::thread(						//将数据处理放进其他线程，分离业务
				[&sum, msg_ptr]() {				//显式捕获，引用捕获数据汇总，值捕获智能指针（防止线程运行时智能指针离开作用域被销毁）
					SalesData book;

					auto obj = msgpack::unpack(msg_ptr->data<char>(), msg_ptr->size()).get();
					obj.convert(book);			//将获取的数据反序列化，转换为自定义对象

					sum.add_sales(book);		//存储数据
				}
			).detach();							//分离线程，异步运行
		}
	};

	auto log_cycle = [&]()						//数据上报循环
	{
		auto http_addr = conf.get<string>("config.http_addr");
		auto time_interval = conf.get<int>("config.time_interval");

		for (;;)								//定时上报
		{
			std::this_thread::sleep_for(time_interval * 1s);

			using json_t = nlohmann::json;
			json_t j;
			j["count"] =						//原子变量转换为int
				static_cast<int>(count);
			j["minmax"] =
				sum.minmax_sales();
#if 0
			auto res = cpr::Post(				//上报数据
				cpr::Url{ http_addr },
				cpr::Body{ j.dump() },
				cpr::Timeout{ 200ms }
			);

			if (res.status_code != 200)			//检查上报结果
				cerr << "http post failed" << endl;
#endif
		}
	};

	auto data_server = std::async(std::launch::async, recv_cycle);
	auto report_server = std::async(std::launch::async, log_cycle);

	report_server.wait();						//启动服务，让程序一直运行下去
}
catch (std::exception& e)
{
	std::cerr << e.what() << std::endl;
}