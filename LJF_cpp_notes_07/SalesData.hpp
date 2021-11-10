//Copyright (c) 2021 by yyyyshen

#ifndef _SALESDATA_HPP
#define _SALESDATA_HPP

#include "cpplang.hpp"

#include <msgpack.hpp>							//用msgpack做序列化

BEGIN_NAMESPACE(yyyyshen)

//
//数据定义
//

class SalesData final							//就是个数据类型，不需要继承
{
public:
	using this_type = SalesData;				//内外类型别名

	using string_type = std::string;
	using const_string_type_ref = const string_type&;
	using uint_type = unsigned int;
	using currency_type = double;
	using buff_type = msgpack::sbuffer;

	STATIC_ASSERT(sizeof(uint_type) >= 4);		//静态断言，检查类型大小（这里其实可以直接用uint32_t这样的类型代替吧？）
	STATIC_ASSERT(sizeof(currency_type) >= 4);	//浮点精度确认
public:
	SalesData(const_string_type_ref id, uint_type s, currency_type r) noexcept
		: m_id(id)
		, m_sold(s)
		, m_revenue(r)							//初始化列表
	{}

	SalesData(const_string_type_ref id) noexcept
		:SalesData(id, 0, 0)					//委托构造
	{}
public:
	SalesData() = default;						//显式将各种构造、析构定义为default
	~SalesData() = default;

	SalesData(const this_type&) = default;		//拷贝
	this_type& operator=(const this_type&) = default;

	SalesData(this_type&&) = default;			//转移；可以避免存入容器时的拷贝，提高效率
	this_type& operator=(this_type&&) = default;

#if 0											//转移实现
	SalesData(this_type&& s) noexcept
		: m_id(std::move(s.m_id))
		, m_sold(std::move(s.m_sold))
		, m_revenue(std::move(s.m_revenue))
	{}

	this_type& operator=(this_type&& s) noexcept
	{
		m_id = std::move(s.m_id);
		m_sold = std::move(s.m_sold);
		m_revenue = std::move(s.m_revenue);

		return *this;
	}
#endif

public:
	MSGPACK_DEFINE(m_id, m_sold, m_revenue);	//msgpack的用法，使用了该宏定义的类就可以实现序列化

	buff_type pack() const
	{
		buff_type sbuf;
		msgpack::pack(sbuf, *this);				//将自身序列化打包

		return sbuf;
	}

	SalesData(const buff_type& sbuf)			//将序列化的数据解析为对象
	{
		auto obj = msgpack::unpack(sbuf.data(), sbuf.size()).get();
		obj.convert(*this);						//将反序列化的对象属性转到自身
	}

private:
	string_type m_id = "";						//简单定义ID号、销售册数、销售金额；成员变量定义时直接初始化
	uint_type m_sold = 0;
	currency_type m_revenue = 0;

public:											//一些取值和修改操作，类似JAVA中bean对象的get/set方法
	void inc_sold(uint_type s) noexcept
	{
		m_sold += s;
	}

	void inc_revenue(currency_type r) noexcept
	{
		m_revenue += r;
	}

	const_string_type_ref id() const noexcept	//只取值，定义为常函数；不抛异常
	{
		return m_id;
	}

	uint_type sold() const noexcept
	{
		return m_sold;
	}

	currency_type revenue() const noexcept
	{
		return m_revenue;
	}
};

END_NAMESPACE(yyyyshen)

#endif // !_SALESDATA_HPP
