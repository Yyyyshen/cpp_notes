//Copyright (c) 2021 by yyyyshen

#ifndef _SPIN_LOCK_HPP
#define _SPIN_LOCK_HPP

#include "cpplang.hpp"

BEGIN_NAMESPACE(yyyyshen)				  //限定命名空间

//自旋锁
// 互斥量成本较高
// 设计一个自旋锁在多线程中保护数据
//

class SpinLock final //禁止继承
{
public:
	using this_type = SpinLock;			  //类型别名
	using atomic_type = std::atomic_flag; //使用了原子变量，成本低，效率高		//atomic_flog，最简单的原子布尔类型只支持两种操作

public:
	SpinLock() = default;				  //使用默认构造和析构
	~SpinLock() = default;

	SpinLock(const this_type&) = delete;  //禁用拷贝（如果不想反复写此类代码，可以利用boost小工具类noncopyable，实现了等价功能，直接继承，避免重复代码）
	this_type& operator=(const this_type&) = delete;

public:
	void lock() noexcept				  //明确知道不会抛异常，用noexcept修饰，尽量高效
	{
		for (;;)
		{
			if (!m_lock.test_and_set())	  //TAS操作，检查flag是否被设置过，若没有，则设置为true，但返回设置前的状态；即已被设置返回true，没设置返回false并设置
				return;					  //返回false则表示成功锁定
			std::this_thread::yield();	  //设置失败则让出线程
		}
	}

	void unlock() noexcept
	{
		m_lock.clear();					  //清除flag状态，即设置为false
	}

	bool try_lock() noexcept
	{
		return !m_lock.test_and_set();	  //由于如果未设置flag，返回的是设置之前的状态，不太直观，封装一下清晰地返回上锁是否成功
	}

private:
	atomic_type m_lock{ false };		  //成员变量直接初始化
};

//保证异常安全
// 利用RAII写一个Guard类
// 构造时加锁，析构时解锁
//

class SpinLockGuard final				  //也可以定义成模板类，适配其他锁
{
public:
	using this_type = SpinLockGuard;
	using spin_lock_type = SpinLock;	  //别名封装

public:									  //禁用拷贝
	SpinLockGuard(const this_type&) = delete;
	this_type& operator=(const this_type&) = delete;

public:
	SpinLockGuard(spin_lock_type& lock) noexcept
		: m_lock(lock)					  //利用初始化列表，并且成员是引用，不能赋值，只能被初始化
	{
		m_lock.lock();
	}

	~SpinLockGuard() noexcept
	{
		m_lock.unlock();
	}

private:
	spin_lock_type& m_lock;
};

END_NAMESPACE(yyyyshen);

#endif // !_SPIN_LOCK_HPP

