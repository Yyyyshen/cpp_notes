//Copyright (c) 2021 by yyyyshen

#ifndef _SUMMARY_HPP
#define _SUMMARY_HPP

#include "cpplang.hpp"

#include "SalesData.hpp"
#include "SpinLock.hpp"

BEGIN_NAMESPACE(yyyyshen)

//
//���ݴ洢��ͳ��
//

class Summary final
{
public:
	using this_type = Summary;					//�ڹ�����������ʱ����������͸�����Ҫ��

	using sales_type = SalesData;				//�������ͱ���
	using lock_type = SpinLock;
	using lock_guard_type = SpinLockGuard;

	using string_type = std::string;			//��Ա���ͱ���
	using map_type = std::map<string_type, sales_type>;
	using minmax_sales_type = std::pair<string_type, string_type>;

public:
	Summary() = default;						//��ʽdefault
	~Summary() = default;

	Summary(const this_type&) = delete;			//���ÿ���
	this_type& operator=(const this_type&) = delete;

private:
	mutable lock_type m_lock;					//������
	map_type m_sales;							//�洢���ۼ�¼�����ǵ�����ͳ�ƣ����ܻ���Ҫ�򵥷�������Ҫ����ʹ������������

public:
	void add_sales(const sales_type& s)			//ҵ����룬������ۼ�¼
	{
		lock_guard_type guard(m_lock);			//����ǰ����

		const auto& id = s.id();				//auto��ȡ��id��������ı䣬������벻�ø�
		if (m_sales.find(id) == m_sales.end())
		{
			m_sales[id] = s;					//û�ҵ������
			return;
		}

		m_sales[id].inc_sold(s.sold());			//�ҵ����޸�����
		m_sales[id].inc_revenue(s.revenue());
	}											//������������Զ�����

	minmax_sales_type minmax_sales() const		//����������һ�����һ������Ҫʵ����minmax_element�㷨
	{
		lock_guard_type guard(m_lock);			//����ǰ����

		if (m_sales.empty())
			return minmax_sales_type();			//����Ϊ�գ�ֱ�ӷ��ؿն���

		auto ret = std::minmax_element(			//�������Сֵ
			m_sales.begin(), m_sales.end(),
			[](const auto& a, const auto& b)	//�Զ���ȽϺ�������ΪĬ�ϱȽϵ���id����ҵ����Ҫ����������
			{
				return a.second.sold() < b.second.sold();
			});

		return { ret.first->second.id(), ret.second->second.id() };
	}
};

END_NAMESPACE(yyyyshen)

#endif // !_SUMMARY_HPP
