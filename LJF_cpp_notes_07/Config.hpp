//Copyright (c) 2021 by yyyyshen

#ifndef _CONFIG_HPP
#define _CONFIG_HPP

#include "cpplang.hpp"

extern "C" {										//luajit，导成C接口
#include <luajit.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <LuaBridge/LuaBridge.h>					//lua与C++交互

BEGIN_NAMESPACE(yyyyshen)

//
//解析配置文件
// 大多数程序都有配置文件保存运行时各种参数，常见的INI、XML、JSON
// 也可以用Lua嵌入C++，用脚本写配置文件
// 使用Lua的好处是，它是编程语言，写起来灵活一些
// 例如添加注释，写一些形如"m * n"的运算配置，而纯文本格式只能写纯数据
// 并且还能直接基于lua写一些函数，校验数据有效性、采集系统信息、动态配置等
// 把Lua当成一个可编程配置语言
// 
// 合理划分C++与Lua职责边界，搭建一个 LuaJIT + LuaBridge + C++ 高性能应用
// LuaJIT使用第三方分支 https://github.com/openresty/luajit2
// LuaBridge https://github.com/vinniefalco/LuaBridge
//

class Config final									//封装读取lua配置文件
{
public:
	using vm_type = std::shared_ptr<lua_State>;		//使用智能指针管理lua虚拟机
	using value_type = luabridge::LuaRef;

	using string_type = std::string;				//用到的类型最好都设置下，毕竟刚开始的设计不一定完善，后期改动的话方便些
	using const_string_type_ref = const string_type&;
	using regex_type = std::regex;
	using match_type = std::smatch;

public:
	Config() noexcept
	{
		assert(m_vm);								//验证有效性
		luaL_openlibs(m_vm.get());					//打开lua基本库，需要传入原始指针，用get获取
	}

public:
	void load(const_string_type_ref filename) const	//解析配置文件，只读，不改变成员变量，应用const修饰；解析可能失败，要抛异常，所以不能用noexcept
	{
		auto status = luaL_dofile(m_vm.get(), filename.c_str());

		if (status != 0)							//解析失败就抛异常
			throw std::runtime_error("failed to parse config");
	}

	template<typename T>
	T get(const_string_type_ref key) const			//处理字符串，获取配置；常函数；模板函数，处理int、string等标准类型
	{
		if (!std::regex_match(key, m_what, m_reg))	//正则匹配，错误抛异常
			throw std::runtime_error("config key error");

		auto key1 = m_what[1].str();				//取出key
		auto key2 = m_what[2].str();
													//通过luabridge获取lua文件中的表
		auto v = luabridge::getGlobal(m_vm.get(), key1.c_str());
		return luabridge::LuaRef_cast<T>(v[key2]);				//在表中取值，并将lua中的值做类型转换成C++
	}

private:
	vm_type m_vm{ luaL_newstate(),lua_close };		//成员虚拟机初始化，shared_ptr自动管理创建和回收
	const regex_type m_reg{ R"(^(\w+)\.(\w+)$)" };	//配置文件中的值采用key1.key2的二级形式，对应lua里的表结构；构造正则成本很高，直接定义为成员，而不是局部变量
	mutable match_type m_what;						//正则匹配结果是临时的，不影响常量性，加上mutable修饰
};


END_NAMESPACE(yyyyshen)

#endif // !_CONFIG_HPP

