// Copyriht (c) 2021 by yyyyshen
#ifndef _CPP_LANG_HPP //Include Guard
#define _CPP_LANG_HPP

//
//核心头文件
//

//集中放置标准头、语言相关定义、其他源文件

#include <iostream>
#include <cassert>			//断言
#include <atomic>			//原子变量
#include <thread>			//线程
#include <regex>			//正则


//宏定义，条件编译，设置兼容性

/*
	这里有个问题，vs使用__cplusplus默认为1997，无法识别项目中使用的C++版本
	需要在项目配置中 C++->命令行->添加 /Zc:__cplusplus 启用宏
*/
#if __cplusplus < 201103 //最低要使用C++11
#	error "C++ version is too old"
#endif //__cplusplus < 201103

#if __cplusplus >= 201402
#	define CPP_DEPRECATED [[deprecated]] //大于C++14启用弃用定义
#else
#	define CPP_DEPRECATED [[gnu::decprecated]] //否则使用gnu的弃用定义
#endif //__cplusplus >=201402

#if __cpp_static_assert >= 201411 
#	define STATIC_ASSERT(x) static_assert(x) //静态断言
#else
#	define STATIC_ASSERT(x) static_assert(x, #x)
#endif

//使用命名空间
#define BEGIN_NAMESPACE(x) namespace x {
#define END_NAMESPACE(x)   }
#define USING_NAMESPACE(x) using namespace x


#endif // !_CPP_LANG_HPP