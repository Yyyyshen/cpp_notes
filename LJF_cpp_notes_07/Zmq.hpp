//Copyright (c) 2021 by yyyyshen

#ifndef _ZMQ_HPP
#define _ZMQ_HPP

#include "cpplang.hpp"

#include <zmq.hpp>

BEGIN_NAMESPACE(yyyyshen)

//
//网络通信模块
// 使用ZMQ
// libzmq环境+cppzmq封装 https://github.com/zeromq
//

using zmq_context_type = zmq::context_t;	//定义常用别名
using zmq_socket_type = zmq::socket_t;
using zmq_message_type = zmq::message_t;

template<int thread_num = 1>				//使用int模板，指定线程数，在编译阶段确认多线程处理能力
class ZmqContext final						//封装底层接口（包装外观）
{
public:
	ZmqContext() = default;					//默认构造析构
	~ZmqContext() = default;

public:
	static									//使用静态成员函数，全部代码集中在hpp，使用::方式调用也更方便
		zmq_context_type& context()
	{										//单例模式封装，静态变量保证线程安全
		static zmq_context_type ctx(thread_num);
		return ctx;
	}

	static
		zmq_socket_type recv_sock(int hwm = 1000, int linger = 10)
	{										//创建接收socket，可能产生异常
		zmq_socket_type sock(context(), ZMQ_PULL);

		//sock.setsockopt(ZMQ_RCVHWM, hwm);	//设置HWM（High Water Mark，本地缓存数量，超过部分阻塞或丢弃）
		//sock.setsockopt(ZMQ_LINGER, linger);

		sock.set(zmq::sockopt::rcvhwm, hwm);//高版本不同的写法
		sock.set(zmq::sockopt::linger, linger);

		return sock;
	}

	static
		zmq_socket_type send_sock(int hwm = 1000, int linger = 10)
	{										//创建发送socket
		zmq_socket_type sock(context(), ZMQ_PUSH);

		//sock.setsockopt(ZMQ_SNDHWM, hwm);
		//sock.setsockopt(ZMQ_LINGER, linger);

		sock.set(zmq::sockopt::sndhwm, hwm);
		sock.set(zmq::sockopt::linger, linger);

		return sock;
	}

};


END_NAMESPACE(yyyyshen)

#endif // !_ZMQ_HPP

