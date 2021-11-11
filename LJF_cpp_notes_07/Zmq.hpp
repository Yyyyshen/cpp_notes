//Copyright (c) 2021 by yyyyshen

#ifndef _ZMQ_HPP
#define _ZMQ_HPP

#include "cpplang.hpp"

#include <zmq.hpp>

BEGIN_NAMESPACE(yyyyshen)

//
//����ͨ��ģ��
// ʹ��ZMQ
// libzmq����+cppzmq��װ https://github.com/zeromq
//

using zmq_context_type = zmq::context_t;	//���峣�ñ���
using zmq_socket_type = zmq::socket_t;
using zmq_message_type = zmq::message_t;

template<int thread_num = 1>				//ʹ��intģ�壬ָ���߳������ڱ���׶�ȷ�϶��̴߳�������
class ZmqContext final						//��װ�ײ�ӿڣ���װ��ۣ�
{
public:
	ZmqContext() = default;					//Ĭ�Ϲ�������
	~ZmqContext() = default;

public:
	static									//ʹ�þ�̬��Ա������ȫ�����뼯����hpp��ʹ��::��ʽ����Ҳ������
		zmq_context_type& context()
	{										//����ģʽ��װ����̬������֤�̰߳�ȫ
		static zmq_context_type ctx(thread_num);
		return ctx;
	}

	static
		zmq_socket_type recv_sock(int hwm = 1000, int linger = 10)
	{										//��������socket�����ܲ����쳣
		zmq_socket_type sock(context(), ZMQ_PULL);

		//sock.setsockopt(ZMQ_RCVHWM, hwm);	//����HWM��High Water Mark�����ػ���������������������������
		//sock.setsockopt(ZMQ_LINGER, linger);

		sock.set(zmq::sockopt::rcvhwm, hwm);//�߰汾��ͬ��д��
		sock.set(zmq::sockopt::linger, linger);

		return sock;
	}

	static
		zmq_socket_type send_sock(int hwm = 1000, int linger = 10)
	{										//��������socket
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

