// Copyriht (c) 2021 by yyyyshen
#ifndef _CPP_LANG_HPP //Include Guard
#define _CPP_LANG_HPP

//
//����ͷ�ļ�
//

//���з��ñ�׼ͷ��������ض��塢����Դ�ļ�

#include <iostream>
#include <cassert>			//����
#include <atomic>			//ԭ�ӱ���
#include <thread>			//�߳�
#include <regex>			//����


//�궨�壬�������룬���ü�����

/*
	�����и����⣬vsʹ��__cplusplusĬ��Ϊ1997���޷�ʶ����Ŀ��ʹ�õ�C++�汾
	��Ҫ����Ŀ������ C++->������->��� /Zc:__cplusplus ���ú�
*/
#if __cplusplus < 201103 //���Ҫʹ��C++11
#	error "C++ version is too old"
#endif //__cplusplus < 201103

#if __cplusplus >= 201402
#	define CPP_DEPRECATED [[deprecated]] //����C++14�������ö���
#else
#	define CPP_DEPRECATED [[gnu::decprecated]] //����ʹ��gnu�����ö���
#endif //__cplusplus >=201402

#if __cpp_static_assert >= 201411 
#	define STATIC_ASSERT(x) static_assert(x) //��̬����
#else
#	define STATIC_ASSERT(x) static_assert(x, #x)
#endif

//ʹ�������ռ�
#define BEGIN_NAMESPACE(x) namespace x {
#define END_NAMESPACE(x)   }
#define USING_NAMESPACE(x) using namespace x


#endif // !_CPP_LANG_HPP