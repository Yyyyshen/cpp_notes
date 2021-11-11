//Copyright (c) 2021 by yyyyshen

#ifndef _CONFIG_HPP
#define _CONFIG_HPP

#include "cpplang.hpp"

extern "C" {										//luajit������C�ӿ�
#include <luajit.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <LuaBridge/LuaBridge.h>					//lua��C++����

BEGIN_NAMESPACE(yyyyshen)

//
//���������ļ�
// ����������������ļ���������ʱ���ֲ�����������INI��XML��JSON
// Ҳ������LuaǶ��C++���ýű�д�����ļ�
// ʹ��Lua�ĺô��ǣ����Ǳ�����ԣ�д�������һЩ
// �������ע�ͣ�дһЩ����"m * n"���������ã������ı���ʽֻ��д������
// ���һ���ֱ�ӻ���luaдһЩ������У��������Ч�ԡ��ɼ�ϵͳ��Ϣ����̬���õ�
// ��Lua����һ���ɱ����������
// 
// ������C++��Luaְ��߽磬�һ�� LuaJIT + LuaBridge + C++ ������Ӧ��
// LuaJITʹ�õ�������֧ https://github.com/openresty/luajit2
// LuaBridge https://github.com/vinniefalco/LuaBridge
//

class Config final									//��װ��ȡlua�����ļ�
{
public:
	using vm_type = std::shared_ptr<lua_State>;		//ʹ������ָ�����lua�����
	using value_type = luabridge::LuaRef;

	using string_type = std::string;				//�õ���������ö������£��Ͼ��տ�ʼ����Ʋ�һ�����ƣ����ڸĶ��Ļ�����Щ
	using const_string_type_ref = const string_type&;
	using regex_type = std::regex;
	using match_type = std::smatch;

public:
	Config() noexcept
	{
		assert(m_vm);								//��֤��Ч��
		luaL_openlibs(m_vm.get());					//��lua�����⣬��Ҫ����ԭʼָ�룬��get��ȡ
	}

public:
	void load(const_string_type_ref filename) const	//���������ļ���ֻ�������ı��Ա������Ӧ��const���Σ���������ʧ�ܣ�Ҫ���쳣�����Բ�����noexcept
	{
		auto status = luaL_dofile(m_vm.get(), filename.c_str());

		if (status != 0)							//����ʧ�ܾ����쳣
			throw std::runtime_error("failed to parse config");
	}

	template<typename T>
	T get(const_string_type_ref key) const			//�����ַ�������ȡ���ã���������ģ�庯��������int��string�ȱ�׼����
	{
		if (!std::regex_match(key, m_what, m_reg))	//����ƥ�䣬�������쳣
			throw std::runtime_error("config key error");

		auto key1 = m_what[1].str();				//ȡ��key
		auto key2 = m_what[2].str();
													//ͨ��luabridge��ȡlua�ļ��еı�
		auto v = luabridge::getGlobal(m_vm.get(), key1.c_str());
		return luabridge::LuaRef_cast<T>(v[key2]);				//�ڱ���ȡֵ������lua�е�ֵ������ת����C++
	}

private:
	vm_type m_vm{ luaL_newstate(),lua_close };		//��Ա�������ʼ����shared_ptr�Զ��������ͻ���
	const regex_type m_reg{ R"(^(\w+)\.(\w+)$)" };	//�����ļ��е�ֵ����key1.key2�Ķ�����ʽ����Ӧlua��ı�ṹ����������ɱ��ܸߣ�ֱ�Ӷ���Ϊ��Ա�������Ǿֲ�����
	mutable match_type m_what;						//����ƥ��������ʱ�ģ���Ӱ�쳣���ԣ�����mutable����
};


END_NAMESPACE(yyyyshen)

#endif // !_CONFIG_HPP

