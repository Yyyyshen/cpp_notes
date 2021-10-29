// LJF_cpp_notes_02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//
//生命周期和编程范式
//

//
//用瀑布模型类比C++程序生命周期
// 编码、预处理、编译、运行
// 
//编码阶段是 C++ 程序生命周期的起点，也是最重要的阶段，是后续阶段的基础，直接决定了 C++ 程序的“生存质量”。
//最基本的要求是遵循语言规范和设计文档，还有代码规范、注释规范、设计模式、编程惯用法，等等。
// 
//预处理是 C/C++ 程序独有的阶段，在这个阶段，发挥作用的是预处理器（Pre - processor）。
//“预处理”的目的是文字替换，用到的就是我们熟悉的各种预处理指令，比如#include、#define、#if 等，实现“预处理编程”。
// 
//编译运行就是将代码经过编译、链接、优化生成可执行文件，并载入内存，CPU逐条语句执行
//后续就是调试、日志跟踪、性能分析等，调整设计思路，重回第一阶段
// 
//应尽量在前三阶段消灭BUG
//

//
//编程范式是一种方法论
// 以 面向过程和面向对象 为基础
// C++支持五种范式，后三种是 泛型、模板元、函数式
// 
//从简洁和可维护角度，常用范式为 过程+对象+泛型 ，少量函数式，慎用模板元（一般是开发面向程序员的Lib才需要深入理解）
//
//



//
//code style
// 
//https://openresty.org/cn/c-coding-style-guide.html
//https://google.github.io/styleguide/cppguide.html
//

//
//较重要的点
//
//留白的艺术
// 在变量和操作符间加空格，在代码块间加空行
// 
//命名风格（这里感觉自己和作者是一样的想法，还不错
// 前缀用 m_表示成员变量 g_表示全局变量
// 变量、函数、空间用全小写+下划线
// 类名用驼峰发
// 宏和常量全大写+下划线
// 后缀用 _t表示type _s表示结构体 _e表示枚举
// 
//写好注释
// 文件头 版权声明、文件名、更新历史、功能描述、todo等
// 函数头 功能说明、注意事项、参数、返回值等
// 
//code review 利于改善风格
// 
//检查工具
// cpplint
//
//



//
//预处理 宏定义 条件编译
//

//
//预处理阶段是将源码改造，包括宏展开和模板实例化等
//虽然在同一个文件中，#开头的预处理指令不受C++语法规则约束
#                              // 预处理空行
#if __linux__                  // 预处理检查宏是否存在
#   define HAS_LINUX    1      // 宏定义，有缩进
#endif                         // 预处理条件语句结束
#                              // 预处理空行
//编译器可以不编译链接，只输出预处理后的代码
// g++ test.cpp -E -o a.cxx
//

//
//包含文件#include
// 不光是包含头文件（只是最常用），而是可以包含任意文件
// 不做检查，将数据合并到源文件，所以为了防止重复包含，通常加入Include Guard
//#ifndef _XXX_H_INCLUDED_
//#define _XXX_H_INCLUDED_
// 头文件内容
//#endif // _XXX_H_INCLUDED_
// 
//除了头文件，还可以编写一些代码片段，存进*.inc文件，然后有选择地加载，实现源码级的抽象
//甚至不只在文件头使用
//例如
static uint32_t  calc_table[] = {  // 非常大的一个数组，有几十行
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba,
	0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
	0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
	//...放在文件里有碍阅读
};
//可以把数值单独拿出来放到文件中，再用include替换
//static uint32_t  calc_table[] = {
//#  include "calc_values.inc"        // 非常大的一个数组，细节被隐藏
//};
//

//
//宏定义#define
// 
//因为宏的展开、替换发生在预处理阶段，不涉及函数调用、参数传递、指针寻址，没有任何运行期的效率损失，
//所以对于一些调用频繁的小代码片段来说，用宏来封装的效果比 inline 关键字要更好（inline发生在编译期），因为它真的是源码级别的无条件内联。
//但也要注意，这意味着宏定义不会进行类型检查等安全措施
//示例（不加分号是为了使用时后面加分号，符合代码的编写和阅读习惯
#define proj_tolower(c) ((c >= 'A' && c <= 'Z') ? (c | 0x20) : c)
#define proj_toupper(c) ((c >= 'a' && c <= 'z') ? (c & -0x20) : c)
#define proj_memzero(buf,n) (void) memset(buf,0,n)
//宏没有作用域概念，全局生效
// 所以对于一些简化代码，起临时作用的宏，用完尽快用#undef取消定义，避免冲突
void
test()
{
#define CUBE(a) (a) * (a) * (a)
	std::cout << CUBE(10) << std::endl;
	//使用若干次
#undef CUBE
}
//用宏定义常量（也不能滥用，还可用enum和const）
#define MAX_BUF_LEN    65535
#define VERSION        "1.0.1"
//发挥文本替换功能
#define BEGIN_NAMESPACE(x) namespace x {
#define END_NAMESPACE(x) }
BEGIN_NAMESPACE(my_space)
//...类和方法等
END_NAMESPACE(my_space)
//形式更醒目
// 

//
//条件编译#if/#else/#endif
// 可根据定义过的宏判断编译环境，产生当前环境最合适的代码，例如跨平台编译
// 
//记住一个宏 __cplusplus，标记了C++语言版本号，判断是C还是C++
#ifdef __cplusplus                      // 定义了这个宏就是在用C++编译
extern "C" {                        // 函数按照C的方式去处理
#endif
	void a_c_function(int a);
#ifdef __cplusplus                      // 检查是否是C++编译
}                                   // extern "C" 结束
#endif

#if __cplusplus >= 201402                // 检查C++标准的版本号
cout << "c++14 or later" << endl;    // 201402就是C++14
#elif __cplusplus >= 201103              // 检查C++标准的版本号
cout << "c++11 or before" << endl;   // 201103是C++11
#else   // __cplusplus < 201103          // 199711是C++98
//#error "c++ is too old"               // 太低则预处理报错
#endif  // __cplusplus >= 201402         // 预处理语句结束
// 
//C++和编译器里都会有一些预定义的宏，可以更精细的通过这些信息来改变代码
// 
//还可以自定义一些宏，实现跨平台处理
#if (PROJ_ANDROID)
#include <proj_android.h>
#elif (PROJ_IOS)
#include <proj_ios.h>
#endif
//
//还有一个特殊用法，可以显示启用或禁用一段代码，比注释更清晰
#if 0          // 0即禁用下面的代码，1则是启用
//...          // 任意的代码
#endif         // 预处理结束
#if 1          // 1启用代码，用来强调下面代码的必要性
//...          // 任意的代码
#endif         // 预处理结束
// 

//
//C++17引入了 __has_include，检查文件是否存在（注意，不是检查文件是否已被包含
//对于Include Guard，
// 可以用指令#pragma once，但是非标准
// C++20引入了module特性，但暂时也无法替代
//boost.preprocessor库可以去看看
//


//
//属性和静态断言
//

//
//在编译阶段，可以用一些指令或者关键字面向编译器编程，显示的告诉它代码某处如何处理，防止有时编译器自作聪明
// 
//属性（没怎么见到有人用过）
// C++11之前，一些编译器有自己的编译指令，如GCC的 __attribute__，VC的__declspec （这个其实比C++的属性更常用，因为它同样适用于C）
// C++11之后，有了正式的编译指令，也就是属性
// 类似于给变量、函数、类贴上标签，给编译器识别处理（类似于JAVA注解？但JAVA注解在编译、类加载、运行时都作用，C++属性仅作用在编译期）
// 没有新的关键字，使用两对方括号表示
// 但C++11只有两个属性 noreturn 和 carries_dependency，作用都不大
[[noreturn]]              // 属性标签
int func(bool flag)       // 函数绝不会返回任何值
{
	throw std::runtime_error("XXX");
}
// C++14定义了较常用的 deprecated 标记不推荐的变量、函数或者类，表示即将废弃
[[deprecated("deadline:2020-12-31")]]      // C++14 or later
int old_func() { return 0; };
// 能正常编译，但会收到警告
// 
//GCC属性文档
// https://gcc.gnu.org/onlinedocs/gcc/Attribute-Syntax.html
//

//
//静态断言
// 
//断言assert
// 判断一个表达式必须为真，否则就会输出错误信息，调用abort终止程序
// assert(p != nullptr);
// 虽然是一个宏，但在预处理阶段不生效，运行时才起作用，又叫动态断言
// 
//static_assert
// 与断言不同，并不是一个宏，而是专门的一个关键字
// 在编译期生效，检查各种条件的静态断言，计算表达式的值，如果值为false，直接编译失败，就不会到运行时才知道
// 例如，保证程序只在64位运行，可以使用这样的检查方式
//static_assert(sizeof(long) == 8, "must run on x64"); //这里有点问题，win64下long也是4字节
// 应该可以用指针长度来确定，更合理一些
static_assert(sizeof(void*) == 8, "must run on x64");
// 由于发生在编译期，所以编译器看不到运行时变量、指针、内存数据等，所以使用范围也并不多
// 
//


//
//面向对象，写好一个类 
//

//
//设计思想，抽象和封装
// 
//即使是C，也能用结构体实现抽象和封装，不一定需要面向对象
// 
//继承
// 主要是为了重用代码，有多态、虚函数、重载等
// 
//实现原则，建议
// 设计类时尽量少用继承和虚函数
// 控制继承层次，最好是只有两层，超过三层就增加了复杂度
// 类应尽量简单那，负责单一功能；若出现多功能混合在一起，应该拆分为多个小类
// 最好不要嵌套类，高内聚必然意味着强耦合，应该使用命名空间，将内部类提出来
// 
//编码准则
// C++11，final（不是关键字，是标识符）显示禁用继承
// class DemoClass final { };
// 必须使用继承时，建议只用public，其他的继承关系让类关系变得复杂，也不常用
// 四大函数，构造、析构、拷贝构造、拷贝赋值，C++11引入和右值rvalue和转移move，多出了转移构造和转移赋值
// （题外话：补充
// 何为左值？能用取址符号 & 取出地址的皆为左值，剩下的都是右值。匿名变量一律属于右值。
// 右值引用也是引用的一种，参数类型为右值引用的函数只能接受右值参数，但不包括模板函数
int i = 1; // i 是左值，1 是右值
int GetZero(){
	int zero = 0;
	return zero;
}
//j 是左值，GetZero() 是右值，因为返回值存在于寄存器中
int j = GetZero();
//s 是左值，string("no name") 是匿名变量，是右值
std::string s = std::string("no name");
// 移动构造函数是参数类型为右值引用的拷贝构造函数
// std::move() 能把左值强制转换为右值。
// 题外话完)
// 六大函数如果不写，编译期会自动生成默认实现，可以用 =default 形式显示的表示出来
class DemoClass final
{
public:
	DemoClass() = default;  // 明确告诉编译器，使用默认实现
	~DemoClass() = default;  // 明确告诉编译器，使用默认实现
};
// 还可以用 =delete 形式明确禁用某个函数形式，但不限于基本函数
// 例如，禁止对象拷贝，可以禁用拷贝构造和拷贝赋值
class DemoClass1 final
{
public:
	DemoClass1(const DemoClass1&) = delete;              // 禁止拷贝构造
	DemoClass1& operator=(const DemoClass1&) = delete;  // 禁止拷贝赋值
};
// C++有隐式构造和隐式转型，在单参数的构造函数，为了防止意外的类型转换，可以用explicit，禁止隐式转换
// class DemoClass2 final
// {
// public:
// 	explicit DemoClass2(const std::string_type& str)  // 显式单参构造函数
// 	{
// 		//...
// 	}
// 	explicit operator bool()                  // 显式转型为bool
// 	{
// 		//...
// 	}
// };
//

//
//常用技巧
// 
//委托构造
// 当类有多个不同形式构造，初始化成员有大量重复代码，可以在一个构造中初始化，其他构造函数都调用它
// 这比把初始化工作封装到一个init()函数中再分别调用更好，提高了效率和可读性
// class DemoDelegating final
// {
// private:
// 	int a;                              // 成员变量
// public:
// 	DemoDelegating(int x) : a(x)        // 基本的构造函数
// 	{}
// 
// 	DemoDelegating() :                 // 无参数的构造函数
// 		DemoDelegating(0)               // 给出默认值，委托给第一个构造函数
// 	{}
// 
// 	DemoDelegating(const std::string& s) : // 字符串参数构造函数
// 		DemoDelegating(stoi(s))        // 转换成整数，再委托给第一个构造函数
// 	{}
// };
// 
//成员变量初始化
// 可以直接将类成员变量在声明时赋值，更易读，也消除了遗漏成员导致未初始化的隐患
// 
//类型别名
// C++11扩展了using的用法，增加了typedef能力，定义类型别名（常用，这样在修改某常用类型时，就可以只变动定义，不需要大量改代码）
using uint_t = unsigned int;        // using别名
typedef unsigned int uint_t;      // 等价的typedef
// 很多外部类型命名很长，可以用using来简化，写代码也方便
// class DemoClass final
// {
// public:
// 	using this_type = DemoClass;          // 给自己也起个别名
// 	using kafka_conf_type = KafkaConfig;        // 外部类起别名
// 
// public:
// 	using string_type = std::string;            // 字符串类型别名
// 	using uint32_type = uint32_t;              // 整数类型别名
// 
// 	using set_type = std::set<int>;          // 集合类型别名
// 	using vector_type = std::vector<std::string>;// 容器类型别名
// 
// private:
// 	string_type     m_name = "tom";              // 使用类型别名声明变量
// 	uint32_type     m_age = 23;                  // 使用类型别名声明变量
// 	set_type        m_books;                      // 使用类型别名声明变量
// 
// private:
// 	kafka_conf_type m_conf;                       // 使用类型别名声明变量
// };
// 
//

//
//其他建议
// 
//C++中不要用typedef struct { } xxx;这样传统的C做法定义结构体
// 
//现在更推荐用*.hpp的方式实现类全部功能，比如boost
//

int main()
{
	std::cout << "Hello World!\n";
	test();

	std::cout << sizeof(long) << std::endl;
}
