#pragma once

#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <unordered_set>
using namespace std;

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