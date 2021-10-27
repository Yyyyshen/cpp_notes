// LJF_cpp_notes_01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//
//学习极客专栏《罗剑锋C++实战笔记》 
//

//
//学前勉言
// 
//任何人都能写出机器能看懂的代码，但只有优秀的程序员才能写出人能看懂的代码。
//有两种写程序的方式：一种是把代码写得非常复杂，以至于“看不出明显的错误”；另一种是把代码写得非常简单，以至于“明显看不出错误”。
//“把正确的代码改快速”，要比“把快速的代码改正确”，容易得太多。
// 
//Stay Hungry, Stay Foolish.
//

//
//环境
// 
//课程推荐Linux，我是mac环境，win和lin虚拟机都有
//个人习惯用vs的git管理，所以项目基本都放在win上
//所以打算使用win+lin两台虚拟机远程编译的方式，在win上管理项目，在lin上测试项目
// 
//升级gcc(n为版本，我的repo环境下最新是10)
//yum -y install centos-release-scl
//yum - y install devtoolset-n-gcc*
//scl enable devtoolset-nbash
//需要注意的是scl命令启用只是临时的，退出shell或重启就会恢复原系统gcc版本
//如果要长期使用的话：
//echo "source /opt/rh/devtoolset-m/enable" >>/etc/profile
//

int main()
{
	std::cout << "Hello World!\n";
}

