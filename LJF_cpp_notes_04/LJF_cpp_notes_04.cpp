// LJF_cpp_notes_04.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <assert.h>
#include <string>
#include <regex>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <numeric>

//标准库

using namespace std;

//
//字符串
//

//
//C++中的string并不是真正的类型，而是typedef了一个模板类的特化
// using string = std::basic_string<char>;
// 
//字符串时字符的序列，有不同的字符类型，多种编码方式
// Unicode，统一处理语言文字，用32位4字节容纳文字
// 而C/C++字符都是单字节char，为了支持不同编码，C++98定义了wchar_t，C++11增加了char16_t、char32_t
// 但处理编码依旧是不够的，需要造轮子，wstring很少用，一般都统一使用utf8，char类型的特化string基本适应大部分场合
// 

// 
//基本功能
// 长度，子串，比较大小，搜索字符等
// 
void
test_string()
{
	string str("abc");
	str.length();
	assert(str < "xyz");
	assert(str.substr(0, 1) == "a");
	assert(str[1] == 'b');
	assert(str.find("1") == string::npos);
	assert(str + "d" == "abcd");
}
// 还有一些类似容器的操作，begin()、end()、push_back()等
// 字符之间为强关系，应看作一个整体，而容器是集合，单个元素之间没关系；所以不要当成容器来用
// 把每个字符串都看作不可变实体才能真正用好
// （如果需要存储字符的容器，例如字节序列、数据缓冲区，可以用vector<char>  ⭐这个确实常用，比char数组要灵活多了）
//

//
//使用技巧
// 
// 字面量后缀
void
test_cpp_string()
{
	using namespace std::literals::string_literals;//上次提到时用不了是因为没有打开这个命名空间（为了避免与用户自定义字面量冲突，必须手动打开）
	/* 命名空间里定义了字面量
		_NODISCARD _CONSTEXPR20_STRING_LITERALS string operator"" s(const char* _Str, size_t _Len) {
			return string(_Str, _Len);
		}
	*/
	auto c_str = "c str";//自动推导出const char*，为c字符
	auto cpp_str = "cpp str"s;//推导类型为string，c++字符
}
// 
// 原始字符串（C++11）
// 格式为R"(str)"
void
test_raw_string()
{
	auto str = R"(raw str)";
	cout << str << endl;
	//这个格式的好处是，不需要写转义字符，并且可以原样输出一些回车符、制表符等
	auto str1 = R"("char")"; //输出 "char"
	auto str2 = R"(\r\n\t\")";//输出 \r\n\t\"
	//嵌套问题
	auto str3 = R"=(R"(str)")=";//使用=为界定符(任意，不大于16个字符)，输出 R"(str)"
}
// 
// 字符串转换
// 与数字相互转换，C中有atoi，atol，参数为C字符而不是string，需要str.c_str()转化一下再用
// C++11提供了一些新的转换函数 stoi stol stof stod等字符串转数字，to_string()转字符串，更方便一些
void
test_stoi()
{
	assert(stoi("42") == 42);
	std::string str("1234");
	int num = atoi(str.c_str());//C用法

	assert(to_string(1234) == "1234");
}
// 
// 字符串视图类
// string成本很重，大字符串的拷贝修改代价高，通常尽量使用const string&
// 但使用C字符串、获取子串等操作无法避免，如果要求优化，需要找轻量级替代品
// C++17有一个string_view，内部只有指针和长度，拷贝、修改成本都很低
// 要在C++11、14项目里使用，可以自己实现一个简易版
class my_string_view final
{
public:
	//内部类型定义
	using this_type = my_string_view;
	using string_type = std::string;
	using string_ref_type = const std::string&;

	using char_ptr_type = const char*;
	using size_type = size_t;
private:
	//成员定义
	char_ptr_type ptr = nullptr;
	size_type len = 0;
public:
	//构造和析构
	my_string_view() = default;
	~my_string_view() = default;
	my_string_view(string_ref_type str) noexcept
		: ptr(str.data())
		, len(str.length())
	{}
public:
	//常用函数...
};
// 
//

//
//正则表达式
// C++11增加了正则库regex，可以匹配字符串
// 
// 两个类
// regex 表示一个正则表达式，是basic_regex的特化
// smatch 表示正则的匹配结果，是match_results特化形式
// 三个算法
// regex_match 完全匹配字符串
// regex_search 字符串里查找一个正则匹配
// regex_replace 正则匹配后再替换
void
test_regex()
{
	auto make_regex = [](const auto& txt)
	{
		return std::regex(txt);//封装一下再用，生成正则
	};
	auto make_match = []()
	{
		return std::smatch();//生产匹配结果
	};
	std::string str("hello:world:111");
	auto reg = make_regex(R"(^(\w+)\:(\w+)$)");//最好使用原始字符串定义表达式，更清晰
	auto what = make_match();//像容器一样，存储匹配结果
	//准备好了两个对象，开始匹配
	assert(regex_match(str, what, reg));
	//看匹配结果
	for (const auto& x : what)
		cout << x << " ";
	cout << endl;
	//替换
	auto new_str = regex_replace(      // 正则替换，返回新字符串
		str,                           // 原字符串不改动
		make_regex(R"(\w+$)"),         // 就地生成正则表达式对象
		"peace"                        // 需要指定替换的文字
	);

	cout << new_str << endl;          // 输出god of peace
}
// 
//

//
//注意事项
// C++20新增了char8_t相当于unsigned char专门表示utf8
// c_str()和data()有区别，都返回const char*指针，但c_str()结尾有'\0'
// boost里有lexical_cast，转换字符串和数字
// 其他第三方正则库，PCRE、Hyperscan、libsregex
//


//
//容器
// 存放元素的数据结构
// 
//通用特性
// 保存元素用值语义，也就是拷贝、副本，而不是引用
// 元素较大或很多时，开销很高，可以为元素实现转移构造和转移赋值函数，用std::move来填进去
// C++11新增emplace操作函数，就地构造元素，免去构造再拷贝、转移的成本，高效也方便些
// v.emplace_back();
// 容器存放指针虽然开销很低，但指针的持有关系，不能利用容器自动销毁的特性，手动管理声明周期容易出错
// 可以考虑存放智能指针
// 
//具体特性
// 顺序容器 array、vector、deque、list、forward_list
//	array，数组，定长
//	vector，数组，动态长度
//	deque，数组，动态长度，两端高效插入删除
//	以上三个都是连续数组，中间插入删除效率低
//	list，双链表结构，插入删除任意位置效率都高，但没有索引，查找效率低
//	forward，单链表
//	链表存储成本比数组高，因为多了指针
//	分配内存时，数组结构的容器双倍扩容，链表结构的固定步长扩容
// （吐槽一下，看了快一半了，全是基础知识，或者一些经典书都有的，这专栏怎么值100多的呢= =）
// 
// 有序容器 set/multiset map/multimap
//	有序的概念，是按照某种规则自动排序，定义容器时必须指定key的比较函数，只不过通常默认是less
//	基本类型都支持默认排序，如果是自定义类型，需要自己重载操作符
//	也可以自定义模板参数，写一个函数作为比较函数
//	每次插入时都会自动排序，含树旋转成本，所以，如果不需要实时排序，最好用vector，全部插入后一次性排序
//	
void test_container()
{
	set<int> s = { 7, 3, 9 };           // 定义集合并初始化3个元素

	for (auto& x : s) {                // 范围循环输出元素
		cout << x << ",";              // 从小到大排序，3,7,9
	}

	auto comp = [](auto a, auto b)  // 定义一个lambda，用来比较大小
	{
		return a > b;                // 定义大于关系
	};

	set<int, decltype(comp)> gs(comp);  // 使用decltype得到lambda的类型

	std::copy(begin(s), end(s),          // 拷贝算法，拷贝数据
			inserter(gs, gs.end()));  // 使用插入迭代器

	for (auto& x : gs) {                // 范围循环输出元素
		cout << x << ",";                // 从大到小排序，9,7,3
	}
}
// 无序容器 unordered前缀的set、map
//	内部结构不是红黑树，而是散列表
//	需要key具备两个条件，可计算hash值，能执行比较操作
//	散列函数最好用标准std::hash对象
auto hasher = [](const auto& p)    // 定义一个lambda表达式
{
	return std::hash<int>()(p.x);  // 调用标准hash函数对象计算
};
//	如果单纯想使用集合或者字典，没有排序要求，就该用无序容器，速度更快
// 
// 
// 容器适配器
// stack、queue、priority_queue，是基于其他容器适配实现的，接口变化，内部结构不变
// 

// 
//选择标准
// 不要有多余操作，按需选择
// 没有特殊需求，最优是vector，速度最快，开销最低
// 只在末尾添加元素的，就不用选deque/list
// 只想快速查找不需要排序的，就选unordered
//

int main()
{
	std::cout << "Hello World!\n";
	//test_raw_string();
	test_regex();
}
