// cpp_standard_01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <cstddef>
#include <vector>
#include <set>
#include <functional>


//
//《C++标准库》-第二版
//

//
//语言特性
// 
void f(int) {};
void f(void*) {};
//nullptr
void
test_nullptr()
{
	//用nullptr取代0或NULL，表示指针指向所谓的no value；避免解释为一个整数值时产生误解
	f(0);						//call f(int)
	f(NULL);					//call f(int)
	f(nullptr);					//call f(void*)
	//std::nullptr_t定义于<cstddef>中，视为一个基础类型
}
//auto
void
test_auto()
{
	auto i = 42;				//int
	//auto声明的变量，类型会根据初值被自动推导，所以，一定有一个初始化操作
	//auto i;					//err			
	static auto vat = 0.19;		//可加额外限定符
	//在长类型或复杂表达式中尤其有用；还有lambda表达式对象类型
	auto lam = [](int x) -> bool
	{
		return true;
	};
}
//一致性初始化和初值列
void
test_init()
{
	//面对任何初始化动作，可以使用相同的语法，就是大括号
	int values[]{ 1,2,3 };
	std::vector<std::string> cities{ "Beijing","Shanghai","Hangzhou" };
	//初值列会强迫值的初始化，某个local变量没有明确初值时会被初始化为0或nullptr
	int i{};//j 0
	int* p{};//p nullptr
	//窄化，精度降低或数值变动，对大括号不成立
	std::vector<int> vec{ 1,2 /* ,3.3  */ };//3.3 err
	//用户自定义类型初值列
	auto print = [](std::initializer_list<int> vals) -> void
	{
		for (auto p = vals.begin(); p != vals.end(); ++p)
			std::cout << *p << " ";
		std::cout << std::endl;
	};
	print({ 1,2,3,4,5 });
	//指明参数个数和指明初值列两种构造函数同时存在，初值列的更优先
	//explicit构造函数如果接受初值列作为参数，则会失去0、1或多个初值隐式转换的能力
}
//Range-based for循环
void
test_range_based_for()
{
	for (int i : {1, 2, 3, 4, 5})
		std::cout << i << " ";
	std::cout << std::endl;
	//容器处理
	std::vector<double> vec;
	for (auto& elem : vec)	//如果不用&声明为引用，则会不断从目标集合拷贝元素；如果是类对象，会不断调用拷贝构造和析构
		elem *= 3;
}
//Move和Rvalue Reference
class X {};
bool operator<(const X& left, const X& right) { return true; }
void
test_move_and_rvalref()
{
	//主要设计目的：避免非必要拷贝和临时对象的产生
	std::set<X> set_x;
	X x;
	set_x.insert(x);
	set_x.insert(x);//两次都插入拷贝对象
	//std::move可转换为右值引用
	set_x.insert(std::move(x));//X&&形式；不再为元素建立拷贝，而是将内部内存赋予新对象（前提是有move构造，否则还是会用copy语义）
	//set_x.insert(x);//编译期不报错，但运行时x已经为空了
}
//字符串字面量 
void
test_string_literal()
{
	//原始字符，不需要转义
	R"(\r\n)";
	//带编码的
	auto str = u8"hello";//char
	auto str2 = L"hello";//wchar_t
	//使用s后缀可以自动推导成std::string，而不是原始C字符

}
//noexcept
void
test_noexcept() noexcept /* 相当于 noexcept(true) */
{
	//声明本函数不打算抛异常，若还是抛了，则abort
	//noexcept不需要stack unwinding，减少编译器产出额外代码，降低开销
	//可以指明一个boolean条件，若条件为true，就不抛异常（无条件noexcept其实是一种简洁形式，如上定义
}
//constexpr
constexpr int
test_constexpr(int x)
{
	//可以让表达式核定于编译期，是真正意义上的常量
	return x * x;
	//const只是无法被改变（也不完全一定）
}
//崭新的Template特性
void test_variadic_template() {}
template<typename T, typename... Args>
void
test_variadic_template(const T& first, Args&... args)
{
	//Variadic template可变参数模板
	std::cout << first << std::endl;
	test_variadic_template(args...);//必须提供一个non-template重载，否则会无法结束递归
}
//别名模板
template<typename T>
using my_vec = std::vector<T>;
//lambda
void
test_lambda()
{
	//以一组方括号引入
	[] { std::cout << "hello world" << std::endl; }();//最简，无参无返回，直接调用
	auto func_obj = [] {};//赋给对象
	//方括号内可指明捕获nonstatic对象，即需要访问的外部数据；方括号和大括号直接可以指定参数
	auto func = [](const std::string& s)
	{
		//func_obj();//err未捕获不能使用
		std::cout << s << std::endl;
	};
	//返回值可以显式用->形式在小括号后写出，不写则是自动推导，相当于返回auto
	[]()->double	//不写推导成int
	{
		return 42;
	};
	//[=]表示外部变量以by value方式传递，[&]表示以by reference方式传递，或指明个别对象
	int x = 0, y = 42;
	auto func2 = [x, &y]()
	{
		//++x;		//err,只可读
		++y;
	};
	//搭配mutable，表示在函数内部可涂写，但它是一份拷贝，不影响外部
	int id = 0;
	auto func3 = [id]()mutable
	{
		++id;
		std::cout << id << std::endl;
	};
	id = 42;
	func3();						//1；lambda捕获的是lambda对象之前出现的值，也就是id=0时
	func3();						//2
	std::cout << id << std::endl;	//42；
}
//lambda的类型，是不具名function object，每个表达式的类型是独一无二的
//如果一定要写出写出类型，可以使用decltype()；或者使用std::function<>
std::function<int(int, int)>
return_lambda()
{
	return [](int x, int y)
	{
		return x + y;
	};
}
void
test_return_lambda()
{
	std::cout << return_lambda()(1, 1) << std::endl;//2
}
//decltype 
template<typename T1, typename T2>
auto add(T1 x, T2 y) -> decltype(x + y)
{
	//新的函数声明语法
}
//带域（scoped）的enum
enum class Week : char { Mon, Tue, Wed };
void
test_enum()
{
	//优点
	//绝不隐式转换
	//避免不明确，要写为Week::Mon
	//显式定义底层类型（:char）保证大小，如果不写默认是int
}
// 
//

int main()
{
	std::cout << "Hello World!\n";
	test_lambda();
	test_return_lambda();
}
