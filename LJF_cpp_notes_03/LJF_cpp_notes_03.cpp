// LJF_cpp_notes_03.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>

//语言特性

using namespace std;

//
//自动类型推导
//

//
//auto
// 
// 使用typedef和using可以简化类型名，但终究需要自己写出来
// 在面对泛型编程中很多带模板参数的复杂类型时，可能都很难正确写出返回值类型
// 而编译器能够判断对错也就意味着它知道正确的类型
// 使用auto就可以自动推导了
void
test_auto()
{
	auto str = "hello";//自动推导不一定完全是自己想要的，这里自动推导为const char[6]，如果想用std::string还是需要自己写
	//C++14新增了字面量后缀s，所以
	//auto str2 = "hello"s;//自动推导出std::string，VS里后缀无效
}
// 其作用并不光是简化代码，还避免了对类型的硬编码，可以根据表达式类型自动适应，比如map和unordered_map
// 变量右边必须有表达式才能使用（赋值、花括号初始化等），纯声明不能用auto
// 另外，类成员变量初始化不能使用auto（静态成员变量可以用，但是还是统一不要用比较好）
class X final {
	//auto m_a = 1;//err
	//void test() { auto a; } //err
};
// auto总是推导出 值类型 ，绝不会是 引用 。
// auto可以附加const、volatile、*、&修饰符
void
test_auto_2()
{
	auto         x = 0L;  //auto推导为long，x为long
	auto* x2 = &x;  //auto推导long，x2为long *
	auto        x3 = &x;  //auto推导long *,x3为long *
	auto& x4 = x;   //auto推导为long，x4为long&
	const auto& x5 = x;   //auto推导为long，x5为const long&
}
//

//
//decltype
// 
// 与auto不同的是，像是一种函数形式的类型推导
void
test_decltype()
{
	int x = 0;
	decltype(x)    x2;//x2为int，相当于直接声明变量，因为自带表达式
	decltype(x)& x3 = x;//x3是int&，而引用必须赋值，所以需要加 =x
	decltype(x)* x4;//x4是int*
	decltype(&x)   x5;//x5为int*
	decltype(&x)* x6;//x6为int**
	//表象上是写法变化，实际的推到规则上，有一个区别：decltype不仅能推导出值类型，还能推导出引用类型
	decltype(x3)   x7 = x;//通过引用类型变量推导出来，x7与x3同样为int&，赋值为x
	auto           x8 = x3;//auto只会推导出引用类型中值的类型，x8为int
	//也就是说，完全可以把decltype当作真正的类型名(int等)，用在任何地方，比如
	using int_ptr = decltype(&x);//int_ptr将代表int*
	using int_ref = decltype(x3);//int_ref将代表int&（使用decltype(x)&也是一样的）
}
// 所以，decltype更精确
// 有一点不方便的，就是写起来麻烦，左边既要写类型计算表达式，右边又要写赋值和初始化的表达式
// C++14加入了一个 decltype(auto) 形式，既可以精确推导，又能像auto一样方便使用
void
test_decltype_auto()
{
	int x = 0;
	decltype(auto) x2 = x;//自动推导为int，x被看作为值
	decltype(auto) x3 = (x);//自动推导为int&，变量加上了括号作为表达式得到的就是一个左值引用
	decltype(auto) x4 = &x;//自动推导为int*
	decltype(auto) x5 = x3;//根据一个引用类型，推导出int&
}
// 
// auto常用方式
//	变量声明
//	遍历容器（最好用 const auto& 保证效率）
//	C++14中增加了返回值使用auto
// 
// decltype
//	配合using
//	例如
//		UNIX信号函数的原型
//		void (*signal(int signo, void (*func)(int)))(int)
//		使用decltype可以轻松得到函数指针类型
//		using sig_func_ptr_t = decltype(&signal);
//	定义类时可以使用（因为auto在类中被禁用）
//


//
//const/volatile/mutable 变量和常量等
//

//
//const
// 定义常量，预处理阶段并不存在，但编译器可能会优化，直接替换
// 准确的说只是不允许修改，应该称为 只读变量
// （C++11的constexpr才是真正的编译阶段常量）
// 所以，虽然变量本身不能修改，但用一个指针获取地址，再写入，是可以破坏常量性的
void
test_const()
{
	int m = 10, n = 100;
	//老生常谈的const声明位置问题
	const int* p_i = &m;
	p_i = &n;
	std::cout << m << ":" << n << std::endl;
	//*p_i = 10; //err
	int* const p_i_2 = &m;//其实很少用到这种情况，但是要理解
	*p_i_2 = 100;
	//p_i_2 = &n; //err
	std::cout << m << ":" << n << std::endl;
	//强行改
	const volatile int LEN = 1024;
	int* ptr = (int*)&LEN;
	*ptr = 2048;
	std::cout << LEN << std::endl; //2048
	const int LEN2 = 1024;
	int* ptr2 = (int*)&LEN2;
	*ptr2 = 2048;
	std::cout << LEN2 << std::endl; //1024，地址处的数值其实已经改了，只不过在编译期这条语句中的LEN2已经被编译器优化替换成了1024，改了也就没有用了
}
//volatile
// 禁止编译器做优化，每次使用修饰的变量都必须去取值，所以上面代码里加了该修饰符的变量，没有在编译期被替换，而是真正取的内存值
// 如果不是明确知道为什么要用这个词，最好不要用
//

//
//const常用场景
// 常量引用和常量指针
// const & 常用于函数的入口参数中，保证效率和安全
// 修饰成员函数，表示执行过程是const的，不会改变对象状态（成员变量）
// const对象无法调用非const成员函数
//

//
//mutable
// const修饰的函数无法修改对象成员，但如果有部分成员变量需要可变，就可以用mutable修饰解除const限制
// 
//


//
//smart_ptr 智能指针
//

//
//指针
// 源自C，本质为内存地址索引，能够直接读写内存，是高效的根源
// 也是各种错误（无效、越界、内存泄露等）出现的原因
// JAVA等语言，内置了垃圾回收机制，C++中是构造/析构和RAII惯用法
// 
//代理模式
// 将原始指针封装，构造里初始化，析构里释放
// 当对象失效后，自动调用析构，完成资源回收
// 智能指针就是根据RAII实现了这些，并重载*和->，使用起来和原指针一样
//

//
//unique_ptr
// 
void
test_unique_str()
{
	std::unique_ptr<int> ptr1(new int(10));//必须初始化，只声明后使用是操作空指针
	//ptr1++; //没有重载加减运算，不能随意移动地址
	auto ptr2 = std::make_unique<int>(10);//unique_ptr的工厂函数，可以防止忘记初始化

	//所有权
	ptr2 = std::move(ptr1);//删除了拷贝赋值，必须用move显示转移所有权，保证持有者唯一
}
// 工厂函数的实现
template<class T, class ... Args>//可变参数模板
std::unique_ptr<T>
my_make_unique(Args&&... args)
{
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
//  
//

//
//shared_ptr
// 与unique_ptr相似，也可以使用工厂函数，重载了*和->操作符
// 最大的不同是所有权可以安全共享可以像原始指针一样，有多个持有者（内部使用引用计数）
// 当引用计数减少到0，才会真正释放
// 语义完整（有拷贝赋值），可以在任何场合代替原始指针而不担心资源回收问题
// 代价就是，引用计数的存储和管理都是成本，过度使用会降低效率
// 指向对象的析构函数不能有过于复杂、阻塞的操作
// 导致新的问题是 循环引用 ，在作为类成员时容易出现
class Node final
{
public:
	using this_type = Node;
	using shared_type = std::shared_ptr<this_type>;
public:
	shared_type     next;      // 使用智能指针来指向下一个节点
};
void
test_shared_ptr()
{
	auto n1 = std::make_shared<Node>();   // 工厂函数创建智能指针
	auto n2 = std::make_shared<Node>();   // 工厂函数创建智能指针

	assert(n1.use_count() == 1);    // 引用计数为1
	assert(n2.use_count() == 1);

	n1->next = n2;                 // 两个节点互指，形成了循环引用
	n2->next = n1;

	assert(n1.use_count() == 2);    // 引用计数为2
	assert(n2.use_count() == 2);    // 无法减到0，无法销毁，导致内存泄漏
}
// 解决循环引用问题，要使用weak_ptr
class Node2 final
{
public:
	using this_type = Node2;

	// 注意这里，别名改用weak_ptr
	using shared_type = std::weak_ptr<this_type>;
public:
	shared_type     next;    // 因为用了别名，所以代码不需要改动
};
void
test_weak_ptr()
{
	auto n1 = std::make_shared<Node2>();  // 工厂函数创建智能指针
	auto n2 = std::make_shared<Node2>();  // 工厂函数创建智能指针

	n1->next = n2;             // 两个节点互指，形成了循环引用
	n2->next = n1;

	assert(n1.use_count() == 1);    // 因为使用了weak_ptr，引用计数为1
	assert(n2.use_count() == 1);   // 打破循环引用，不会导致内存泄漏

	if (!n1->next.expired()) {     // 检查指针是否有效
		auto ptr = n1->next.lock();  // lock()获取shared_ptr
		assert(ptr == n2);
	}
}
// 
//


//
//exception 异常
//

//
//很多人认为，C++中出现异常一般是很严重的，在之前（以及C中）的基本手段是使用错误码
// 函数执行后，检查返回值或错误码，验证是否正常，出错则执行另一段代码处理
// 正常业务逻辑代码和错误处理代码混在一起，不够清晰
// 另外，错误码可能会被忽略，错误得不到处理，运行到之后时有隐患
// 
//使用异常
// 抛出和处理时独立的，throw之后可以不用管，catch块专门处理，逻辑分离
// 无法被忽视，必须在catch中捕获
// 可以使用在错误码无法使用的场合，C++中很多函数没有返回值，或无法表示错误
// 
//如何用好异常
// 虽然throw可以抛出任何类型，但最好使用标准的异常类型体系，派生出自己的异常类
// 抛出时不要直接使用throw，封装成函数，通过引入一个中间层获得更多可读性和安全性，代码也灵活些
class my_exception : public std::runtime_error
{
public:
	using this_type = my_exception;        // 给自己起个别名
	using super_type = std::runtime_error;  // 给父类也起个别名
public:
	my_exception(const char* msg) :            // 构造函数
		super_type(msg)                      // 别名也可以用于构造
	{}

	my_exception() = default;                // 默认构造函数
	~my_exception() = default;                // 默认析构函数
private:
	int code = 0;                            // 其他的内部私有数据
};
[[noreturn]]
void
raise(const char* msg)
{
	throw my_exception(msg);
}
// catch捕获异常时，时根据代码里的顺序一次匹配，而不会自动匹配最佳，所以，最好只用一个catch块，绕过这个坑
// catch块入口参数最好使用 const & 形式，避免拷贝代价
// function-try 形式，将整个函数体视为大的try块，catch块放在后面与函数体同级并列
//	可以捕获函数中所有可能异常，并且少了一级缩进层次（也有人认为异常处理效率很低，应该try尽量少的内容）
void
some_function()
try
{
	//函数体
}
catch (...) {
	//处理异常
}
// 
//

//
//三种使用异常的观点
// 绝不用异常，只用错误码
// 全面使用异常，但异常处理需要栈展开（stack unwind）操作，如果发生位置很深或频繁抛出，性能影响很大
// 区分错误轻重成都，折中使用异常
// 
//应当使用异常的推荐情况
// 不允许被忽略的错误
// 极少数发生的错误（读写文件）
// 严重影响正常流程的错误（构造函数，内部初始化失败，无法创建则后面逻辑无法进行）
// 无法本地处理，必须穿透调用栈到上层才能被处理的错误
// （socket通信这种由于网络链路不稳定因素太多，出现频率很高，所以检查错误码方式会更好）
//

//
//noexcept
// 编译阶段指令，修饰函数，告诉编译期该函数不会抛出异常，就可以对函数优化，不加栈展开的额外代码，消除一些成本
void func_noexcept() noexcept
{
	//和const一样放在函数后面
	//但内部写throw不会被禁止，noexcept只是对外宣称无异常，如果真的发生，就直接崩溃了
}
// 一般认为，重要的构造函数和析构函数应该尽量声明为noexcept，优化性能（析构是必须保证绝不会抛异常）
// noexcept可以当作运算符，指定某条件下不会抛异常
//

//
//其他分享
// 磁盘操作 异常+调用栈
// 业务逻辑 日志+调用栈
// 指针和内存分配 日志+调用栈
//


//
//lambda
//

//
//函数式编程
// 

void my_square(int x)           // 定义一个函数
{
	cout << x * x << endl;       // 函数的具体内容
}
void test_func_ptr() {
	auto pfunc = &my_square;       // 只能用指针去操作函数，指针不是函数
	(*pfunc)(3);                    // 可以用*访问函数
	pfunc(3);                       // 也可以直接调用函数指针
}
// 简单lambda
void test_lambda() {
	auto func = [](int x) //函数是全局的，没有生存周期概念，并且也不允许嵌套函数
	{					  //lambda表达式则是一个变量，可以就地定义，作用域就是所在函数内
		cout << x + x << endl;
	};
	func(3);
}
// 捕获外部变量
void test_closure() {
	int n = 10;
	auto func = [=](int x)
	{
		cout << x * n << endl;
	};
	func(3);
}
// 
//

//
//lambda形式
// [] 引出符
// 引出符后面接()像普通函数一样声明入口函数
// 用花括号定义函数体
// auto f = [](){}; //最简单的lambda空函数
// 
// 要有良好的缩进格式，否则嵌套定义时可读性很差
void test_lambda_2() {
	auto f2 = []()                 // 定义一个lambda表达式
	{
		cout << "lambda f2" << endl;

		auto f3 = [](int x)         // 嵌套定义lambda表达式
		{
			return x * x;
		};// lambda f3              // 使用注释显式说明表达式结束

		cout << f3(10) << endl;
	};  // lambda f2               // 使用注释显式说明表达式结束
}
// 每个lambda表达式都有一个特殊类型，所以都使用auto来声明
// 而一般来说，lambda在应用时一般都是匿名使用的临时对象，纯右值，运行后就释放了，这样可以最小化影响范围，增加安全性
void test_lambda_3() {
	vector<int> v = { 3, 1, 8, 5, 0 };     // 标准容器

	cout << *find_if(begin(v), end(v),   // 标准库里的查找算法
		[](int x)                // 匿名lambda表达式，不需要auto赋值
		{
			return x >= 5;        // 用做算法的谓词判断条件 
		}                        // lambda表达式结束
	)
		<< endl;                        // 语句执行完，lambda表达式就不存在了
}
// 
// []捕获规则
// [=]表示按值捕获所有外部变量，表达式内部是值的拷贝，不能修改
// [&]表示按引用捕获所有外部变量，内部是引用的方式使用，能修改
// []内明确写出外部变量名，指定按值或引用方式捕获
void test_lambda_4() {
	int x = 100;
	int y = 10;
	auto f1 = [=]()
	{
		//x = 10;//error
	};
	auto f2 = [&]()
	{
		x = 10;//可修改
	};
	auto f3 = [x]()
	{
		//x = 100;//error
	};
	auto f4 = [=, &x]() //规则表示，除了x以应用方式捕获，其他按值
	{
		x = 100;
		//y = 10; //error，y还是按值捕获，不能修改
	};
}
// 外部变量 是lambda表达式定义之前出现的所有变量，无论局部还是全局
// =号捕获是独立副本，非常安全
// &号捕获的引用，存在风险，如果lambda表达式在里定义点较远地方调用，引用可能已经发生了变化甚至失效了，可能导致不可预期结果
// 所以，应尽量显示写出要捕获的变量
class DemoLambda final
{
private:
	int x = 0;
public:
	auto print()              // 返回一个lambda表达式供外部使用
	{
		return [this]() -> void     // 显式捕获this指针
		{
			cout << "member = " << x << endl;
		};
	}
};
// 
//

//
//lambda泛型化
// 相当于简化的模板函数
void test_template_lambda() {
	auto f = [](const auto& x)
	{
		return x + x;
	};
	cout << f(3) << endl;//int
	cout << f(3.14) << endl;//double
	cout << f(std::string("hello")) << endl;
}
// 
// 

// 
// lambda不支持fucntion-try形式，只能内部try catch
// 返回值类型可以自动推导，但有时必须明确返回值类型，格式为在圆括号后用 “ -> type ” 形式定义返回值
// 按值捕获是，可以给lambda表达式加mutable修饰，允许修改变量，但修改的也只是拷贝，不影响外部原值
// 如果长期持有外部变量，可以考虑使用shared_ptr避免变量失效
// 每个lambda表达式类型都唯一，所以即使函数签名相同，也不能互相赋值，可以使用std::function类，存储任意符合签名的可调用物，搭配lambda表达式使用
//

int main()
{
	std::cout << "Hello World!\n";
	test_const();
	test_template_lambda();
}
