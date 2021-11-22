// cpp_standard_05.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//
//I/O
//

//
//Stream
// 基本类和全局对象
// 读 istream
//  cin
// 写 ostream
//  cout、cerr，clog
// 
// 操作符 << >>
// 操控器
//  std::cout << std::endl;
void
test_manipulator()
{
	//一些ostream操控器
	std::cout << std::endl;	//endl，输出\n并刷新缓冲区
	std::cout << std::ends;	//ends，输出\0
	std::cout << std::flush;//刷新output缓冲区
	//istream操控器
	std::cin >> std::ws;	//读入并忽略空白符

	//特殊类型，比printf更灵活的输出
	const char* cstr = "hello";
	std::cout << cstr << " : " << (void*)cstr << std::endl;

	//状态
	if (std::cin.fail())
		return;

}
// 
//

int main()
{
	std::cout << "Hello World!\n";
}
