//Copyright (c) 2021 by yyyyshen

#ifndef _SUMMARY_HPP
#define _SUMMARY_HPP

#include "cpplang.hpp"

#include "SalesData.hpp"
#include "SpinLock.hpp"

BEGIN_NAMESPACE(yyyyshen)

//
//数据存储和统计
//

class Summary final
{
public:
	using this_type = Summary;					//在关联了其他类时，定义别名就更加重要了

	using sales_type = SalesData;				//关联类型别名
	using lock_type = SpinLock;
	using lock_guard_type = SpinLockGuard;

	using string_type = std::string;			//成员类型别名
	using map_type = std::map<string_type, sales_type>;
	using minmax_sales_type = std::pair<string_type, string_type>;

public:
	Summary() = default;						//显式default
	~Summary() = default;

	Summary(const this_type&) = delete;			//禁用拷贝
	this_type& operator=(const this_type&) = delete;

private:
	mutable lock_type m_lock;					//自旋锁
	map_type m_sales;							//存储销售记录，考虑到除了统计，可能还需要简单分析，需要排序，使用了有序容器

public:
	void add_sales(const sales_type& s)			//业务代码，添加销售记录
	{
		lock_guard_type guard(m_lock);			//操作前上锁

		const auto& id = s.id();				//auto获取，id类型如果改变，这里代码不用改
		if (m_sales.find(id) == m_sales.end())
		{
			m_sales[id] = s;					//没找到则添加
			return;
		}

		m_sales[id].inc_sold(s.sold());			//找到则修改数据
		m_sales[id].inc_revenue(s.revenue());
	}											//作用域结束，自动解锁

	minmax_sales_type minmax_sales() const		//计算销量第一和最后一名，主要实践下minmax_element算法
	{
		lock_guard_type guard(m_lock);			//操作前上锁

		if (m_sales.empty())
			return minmax_sales_type();			//容器为空，直接返回空对象

		auto ret = std::minmax_element(			//求最大最小值
			m_sales.begin(), m_sales.end(),
			[](const auto& a, const auto& b)	//自定义比较函数，因为默认比较的是id，而业务需要用销量排序
			{
				return a.second.sold() < b.second.sold();
			});

		return { ret.first->second.id(), ret.second->second.id() };
	}
};

END_NAMESPACE(yyyyshen)

#endif // !_SUMMARY_HPP
