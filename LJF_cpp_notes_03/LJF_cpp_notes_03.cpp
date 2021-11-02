// LJF_cpp_notes_03.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

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

int main()
{
	std::cout << "Hello World!\n";
	test_const();
}
