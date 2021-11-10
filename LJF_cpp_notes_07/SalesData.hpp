//Copyright (c) 2021 by yyyyshen

#ifndef _SALESDATA_HPP
#define _SALESDATA_HPP

#include "cpplang.hpp"

#include <msgpack.hpp>							//��msgpack�����л�

BEGIN_NAMESPACE(yyyyshen)

//
//���ݶ���
//

class SalesData final							//���Ǹ��������ͣ�����Ҫ�̳�
{
public:
	using this_type = SalesData;				//�������ͱ���

	using string_type = std::string;
	using const_string_type_ref = const string_type&;
	using uint_type = unsigned int;
	using currency_type = double;
	using buff_type = msgpack::sbuffer;

	STATIC_ASSERT(sizeof(uint_type) >= 4);		//��̬���ԣ�������ʹ�С��������ʵ����ֱ����uint32_t���������ʹ���ɣ���
	STATIC_ASSERT(sizeof(currency_type) >= 4);	//���㾫��ȷ��
public:
	SalesData(const_string_type_ref id, uint_type s, currency_type r) noexcept
		: m_id(id)
		, m_sold(s)
		, m_revenue(r)							//��ʼ���б�
	{}

	SalesData(const_string_type_ref id) noexcept
		:SalesData(id, 0, 0)					//ί�й���
	{}
public:
	SalesData() = default;						//��ʽ�����ֹ��졢��������Ϊdefault
	~SalesData() = default;

	SalesData(const this_type&) = default;		//����
	this_type& operator=(const this_type&) = default;

	SalesData(this_type&&) = default;			//ת�ƣ����Ա����������ʱ�Ŀ��������Ч��
	this_type& operator=(this_type&&) = default;

#if 0											//ת��ʵ��
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
	MSGPACK_DEFINE(m_id, m_sold, m_revenue);	//msgpack���÷���ʹ���˸ú궨�����Ϳ���ʵ�����л�

	buff_type pack() const
	{
		buff_type sbuf;
		msgpack::pack(sbuf, *this);				//���������л����

		return sbuf;
	}

	SalesData(const buff_type& sbuf)			//�����л������ݽ���Ϊ����
	{
		auto obj = msgpack::unpack(sbuf.data(), sbuf.size()).get();
		obj.convert(*this);						//�������л��Ķ�������ת������
	}

private:
	string_type m_id = "";						//�򵥶���ID�š����۲��������۽���Ա��������ʱֱ�ӳ�ʼ��
	uint_type m_sold = 0;
	currency_type m_revenue = 0;

public:											//һЩȡֵ���޸Ĳ���������JAVA��bean�����get/set����
	void inc_sold(uint_type s) noexcept
	{
		m_sold += s;
	}

	void inc_revenue(currency_type r) noexcept
	{
		m_revenue += r;
	}

	const_string_type_ref id() const noexcept	//ֻȡֵ������Ϊ�������������쳣
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
