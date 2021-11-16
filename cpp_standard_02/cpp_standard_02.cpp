// cpp_standard_02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//
//一般概念
//

//
//命名空间
// 使用标识符
// 直接指定命名空间 
//  std::string
// 使用using declaration
//  using std::cout
// 使用using directive（大项目中尽量避免使用，容易产生不明确）
//  using namespace std
//

//
//头文件
// 重新规范标准头文件名称，不使用扩展名
#include <string>
#include <cstring>
// 兼容旧式文件头
//

//
//差错和异常处理
// std::exception
//

//
//可被调用对象
// 普通函数
// 函数指针
// 函数对象（拥有operator()）
// lambda表达式对象
//

//
//并发和多线程
// 标准库类型一般都是非线程安全，需要额外提供保障
//

//
//分配器
// 在处理对象内存分配和归还时，用到allcoator
// 默认的分配器会执行一般性收费，就是new和delete
// 少数情况才会需要自行写
//


int main()
{
    std::cout << "Hello World!\n";
}
