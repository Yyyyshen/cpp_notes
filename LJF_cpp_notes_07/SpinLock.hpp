//Copyright (c) 2021 by yyyyshen

#ifndef _SPIN_LOCK_HPP
#define _SPIN_LOCK_HPP

#include "cpplang.hpp"

BEGIN_NAMESPACE(yyyyshen)				  //�޶������ռ�

//������
// �������ɱ��ϸ�
// ���һ���������ڶ��߳��б�������
//

class SpinLock final //��ֹ�̳�
{
public:
	using this_type = SpinLock;			  //���ͱ���
	using atomic_type = std::atomic_flag; //ʹ����ԭ�ӱ������ɱ��ͣ�Ч�ʸ�		//atomic_flog����򵥵�ԭ�Ӳ�������ֻ֧�����ֲ���

public:
	SpinLock() = default;				  //ʹ��Ĭ�Ϲ��������
	~SpinLock() = default;

	SpinLock(const this_type&) = delete;  //���ÿ�����������뷴��д������룬��������boostС������noncopyable��ʵ���˵ȼ۹��ܣ�ֱ�Ӽ̳У������ظ����룩
	this_type& operator=(const this_type&) = delete;

public:
	void lock() noexcept				  //��ȷ֪���������쳣����noexcept���Σ�������Ч
	{
		for (;;)
		{
			if (!m_lock.test_and_set())	  //TAS���������flag�Ƿ����ù�����û�У�������Ϊtrue������������ǰ��״̬�����ѱ����÷���true��û���÷���false������
				return;					  //����false���ʾ�ɹ�����
			std::this_thread::yield();	  //����ʧ�����ó��߳�
		}
	}

	void unlock() noexcept
	{
		m_lock.clear();					  //���flag״̬��������Ϊfalse
	}

	bool try_lock() noexcept
	{
		return !m_lock.test_and_set();	  //�������δ����flag�����ص�������֮ǰ��״̬����ֱ̫�ۣ���װһ�������ط��������Ƿ�ɹ�
	}

private:
	atomic_type m_lock{ false };		  //��Ա����ֱ�ӳ�ʼ��
};

//��֤�쳣��ȫ
// ����RAIIдһ��Guard��
// ����ʱ����������ʱ����
//

class SpinLockGuard final				  //Ҳ���Զ����ģ���࣬����������
{
public:
	using this_type = SpinLockGuard;
	using spin_lock_type = SpinLock;	  //������װ

public:									  //���ÿ���
	SpinLockGuard(const this_type&) = delete;
	this_type& operator=(const this_type&) = delete;

public:
	SpinLockGuard(spin_lock_type& lock) noexcept
		: m_lock(lock)					  //���ó�ʼ���б����ҳ�Ա�����ã����ܸ�ֵ��ֻ�ܱ���ʼ��
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

