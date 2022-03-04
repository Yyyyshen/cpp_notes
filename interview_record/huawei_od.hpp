#pragma once

#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <unordered_set>
using namespace std;

//
//华为OD
// 电话沟通后了解到OD就是先挂名其他企业，一年后有机会转正，也就是外包性质
// 据说转正概率并不高
// 
// 第一轮笔试，机考，发了练习题链接
// 编程练习题 
//  https://blog.csdn.net/armstronghappy/article/details/119236183
// 考试信息
// a 严格按照测试用例得分，第一题是简单点的两小题每题是100分；
// 第二题难点一题200分，第一题提交后不能返回，提交后才能看第二题，
// 时间总共2.5小时，控制时间，如果没有把握起码先把前两个题做了
// b 牛客网leetcode编程的时候输入输出是设置好的，但是实际考试过程需要自己写，
// 所以练习牛客网的时候用考试模式（进企业版在线考试试用），考试模式就需要自己写输入输出
// 
//刷了几道题之后感觉两天时间准备50道有点困难
// 看到网上说可以直接刷牛客的华为机试题
// https://www.nowcoder.com/ta/huawei
// 
//关键字
// 刷题 试用考试模式 外包性质
//

//
//3.2 晚六点机考
// 记录
// 
//题1：三数组合
// 三数之和题变种，条件是找 A = B + 2C
// 变化就是两个数字谁当C，分了两种情况分别找了一遍
// AC 100%
// 
//题2：最大括号深度
// 力扣有类似题型，相同的思路做了
// 不同的是此题目只要没有完全闭合就不算合法括号
// 例如 ([)] 
// 合法 ([]{[]}) 合法，嵌套深度3
// 感觉思路是对的，但是有些用例想不到
// AC 70%
// 
//题3：最大网络响应
// 给定一组数据组成一个有向图
// 再给一个节点值
// 从节点发送广播，求收到所有节点回复的最大响应时间
// 例如
// 5 7 （五个节点 七组数据）
// 2 1 （从节点2->节点1）
// 2 3
// 1 4
// 2 4
// 4 5
// 3 5
// 3 4
// 2   （从节点2发送广播）
// 输出 4
// 题目条件保证所有节点可达
// 
// 我的思路是对每个节点的每条路径都进行记录，类似邻接矩阵
// 然后找所有从发送节点开始的路径
// 每条路径遍历经过的节点，使用一个map记录到其他节点的最小路径
// 最后最小路径乘2
// 
// 虽然对图不是很熟悉，但觉得思路也应该对
// 不过通过率很低，还要再研究下
// AC 10%
//

//
//3.3 早上沟通
// 机考分数与自己估的一致
// 400满
// 100 * 100% + 100 * 70% + 200 * 10% = 190
// 
// 评价：
//	编码能力还是OK的 思路规范性正确性都还可以的
// 
// 估计只要不是完全做不出来都会走一下流程吧，算是有个排位的机会
// 
//当天下午做综合测试
// 类似调查问卷
// 考查心理素质和情绪控制 这一块 抗压性啊 乐观度啊之类了
// 
//另外
// 要了电子版简历，突然想到还没做
//

//
//3.4 下午沟通
// 综合测评过了
// 
// 评价：
// 没啥问题，挺好的
// 
//准备安排技术面试
// 发了机考试题第三题，估计技术面还会问，再研究下
// 另外回顾一下项目
//

//
//华为OD提供的练习题记录
//

//接雨水（hard） /problems/trapping-rain-water/
class Solution {
public:
	int trap(vector<int>& height) {
		//暴力，遍历，每次找本格左右两边最高的墙壁，那么本格存水量就是左右最高中最低一面墙减自己的高度
#if 0
		if (height.empty()) return 0;
		int ret = 0;
		for (int i = 0; i < height.size(); ++i)
		{
			int left_max = 0, right_max = 0;
			for (int j = i; j >= 0; --j)
				left_max = max(height[j], left_max);
			for (int j = i; j < height.size(); ++j)
				right_max = max(height[j], right_max);
			ret += min(left_max, right_max) - height[i];
		}
		return ret;
#endif
		//DP，把左右两边最高的值先记录下来，遍历的时候直接用，而不是每次都重新算一遍
#if 0
		if (height.empty()) return 0;
		int n = height.size(), ret = 0;
		vector<int> left_max(n), right_max(n);
		left_max[0] = height[0];
		for (int i = 1; i < n; ++i)
			left_max[i] = max(left_max[i - 1], height[i]);
		right_max[n - 1] = height[n - 1];
		for (int i = n - 2; i >= 0; --i)
			right_max[i] = max(right_max[i + 1], height[i]);
		for (int i = 0; i < n; ++i)
			ret += min(left_max[i], right_max[i]) - height[i];
		return ret;
#endif
		//双指针，动态规划中左右最大其实只用一次，其实可以不存在数组中，优化空间
		//然后从左右两边分别开始往中间找，哪边更小，就计算哪一边（更小的一边的数值才是有效的最小值）
		if (height.empty() || height.size() < 3/* 至少是凹字形才能存水 */) return 0;
		int size = height.size(), ret = 0;
		int left = 0, right = size - 1;
		int left_max = 0, right_max = 0;
		while (left < right)
		{
			left_max = max(left_max, height[left]);
			right_max = max(right_max, height[right]);
			if (left_max <= right_max)
				ret += left_max - height[left];
			else
				ret += right_max - height[right--];
		}
		return ret;
		//栈，类似括号匹配，用栈记录凹字形的范围，但思路比较困难
		//看一下官方解法
		int ans = 0, current = 0;
		stack<int> st;
		while (current < height.size()) {
			while (!st.empty() && height[current] > height[st.top()]) {
				int top = st.top();
				st.pop();
				if (st.empty())
					break;
				int distance = current - st.top() - 1;
				int bounded_height = min(height[current], height[st.top()]) - height[top];
				ans += distance * bounded_height;
			}
			st.push(current++);
		}
		return ans;
	}
};

//字符串压缩（easy） https://leetcode-cn.com/problems/compress-string-lcci/
string compressString(string S)
{
	if (S.empty()) return S;
	string ret;
	ret += S[0];
	int count = 1;
	for (int i = 1; i < S.size(); ++i)
	{
		if (S[i] == S[i - 1])
			++count;
		else
		{
			ret += to_string(count);
			count = 1;
			ret += S[i];
		}
	}
	//最后还要把最后一个字符的次数加进去
	ret += to_string(count);
	return S.size() <= ret.size() ? S : ret;
}

//俄罗斯套娃信封（hard） /problems/russian-doll-envelopes/
int maxEnvelopes(vector<vector<int>>& envelopes) {
	//普通dp O(logn+n^2)
	if (envelopes.empty() || envelopes[0].size() != 2) return 0;
	//先按宽高排序，对比函数写或不写都是一样的结果
	sort(envelopes.begin(), envelopes.end(),
		[](const vector<int>& a, const vector<int>& b) {
			if (a[0] == b[0])
				return a[1] < b[1];
			return a[0] < b[0];
		});
	int size = envelopes.size(), ret = 1;
	vector<int> dp(size, 1);
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			//每个信封看能否装的下前面的每个信封，装得下说明也装得下该信封里面的信封
			if (envelopes[i][0] > envelopes[j][0] && envelopes[i][1] > envelopes[j][1])
			{
				dp[i] = max(dp[i], dp[j] + 1);
				ret = max(ret, dp[i]);//同时记录最大值，避免再一次遍历
			}
		}
	}
	return ret;
	//抽象为计算最长递增序列，以贪心思想计算，但有一个注意点如下
	sort(envelopes.begin(), envelopes.end(),
		[](const vector<int>& a, const vector<int>& b) {
			//这里普通排序不能完成任务，既然是递增序列，那么尽可能的让宽高的二维降为一维
			//也就是宽相等时，让高度更高的排在前面，以便能用贪心的思想求出当前最大递增的情况
			if (a[0] == b[0])
				return a[1] > b[1];
			return a[0] < b[0];
		});
	//递增子序列记录，尽可能小的记录元素
	vector<int> lis;
	for (auto& pair : envelopes)
	{
		//宽元素已排序，比较高元素
		auto iter = lower_bound(lis.begin(), lis.end(), pair[1]);
		if (iter == lis.end())
			lis.push_back(pair[1]);
		else if (*iter > pair[1])
			*iter = pair[1];
	}
	return lis.size();
}

//网络延迟时间（medium） /problems/network-delay-time/
int networkDelayTime(vector<vector<int>>& times, int n, int k) {
	
}