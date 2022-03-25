#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
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
//时间：
// 下周一晚上7点
// 
//另外
// 从截图看到参加机考的人数140，最后一题平均分20+
//

//
//3.7 技术1面
// welink会议面试 晚上七点
// 机考题第三题又复盘了一下，另外回顾一些底层知识
// 
//一道算法题开场
// 最大连续0的个数
// 一个数组含有0和1，可把k个0替换为1，问最大连续0的个数
int longestZeros(vector<int>& A, int k)
{
	//滑动窗口
	int left = 0, right = 0, ret = 0;
	int size = A.size();
	//记录1的个数
	int ones = 0;
	while (right < size) {
		//如果往右滑动过程中，是1则可替换，计数
		if (A[right] == 1)
			++ones;
		//可替换数超过指定数，则缩短窗口
		while (ones > k)
			if (A[left++] == 1)
				--ones;
		//整个窗口记录的是包含小于等于k个1窗口
		ret = max(ret, right - left + 1);
		++right;
	}
	return ret;
}
// 思路讲解完开始面试
// 
//面试问题
// 项目相关，难点解决
// 
// io复用，select、poll、epoll区别
// tcp协议、流量控制
// domain socket
//  https://www.cnblogs.com/sparkdev/p/8359028.html
// 内存屏障（编译器优化，指令乱序）
//  https://blog.csdn.net/GugeMichael/article/details/8207519
//  https://wingsxdu.com/posts/note/cpu-cache-and-memory-barriers/
//	知道volatile这个是防止编译器优化的，但没想到是指令乱序和内存屏障这两个词汇相关
// CAS原语 
//	http://www.zyiz.net/tech/detail-129644.html
//  http://www.pksure.com/backend/jdk/concurrent-cas
//	看到过但是忘了
// 协程和线程的区别
//  https://www.bilibili.com/read/cv9346691
// 互斥量和自旋锁
//  https://www.jianshu.com/p/4b097aac2c9d
// 缓存
// 内存置换、分页分段
// malloc申请虚拟内存后不写不占用物理内存
// 寄存器有哪些
//  寄存器%rdi, %rsi, %rdx, %rcx, %r8, %r9 分别用来保存函数的 6 个参数，而 %rax 用来保存函数的返回值。
// 参数入哪个寄存器
//  https://blog.csdn.net/qq_31917799/article/details/104233427
// linux常用命令 readelf objdump
//  https://blog.csdn.net/u014608280/article/details/81948141
// gcc命令
//  https://wangchujiang.com/linux-command/c/gcc.html
// shell命令
//  https://www.runoob.com/linux/linux-command-manual.html
// 堆排序
// 
//有少部分没有答上来，等HR反馈
// 
//3.8 技术一面反馈
// 通过，还不错
// 继续准备，等时间安排技术二面
// 形式与一面相同，是其他部门的交叉面试
//

//
//3.10 通知晚上7点技术二面
// 
//再过一遍基本知识，看几道题
// 
//面试记录
// 自我介绍
// 项目难点
// 网络知识 tcp连接过程
// 
// 一道算法题
/*
以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。
请你合并所有重叠的区间，并返回一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间。
	示例 1：
	 
	输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
	输出：[[1,6],[8,10],[15,18]]
	解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
*/
class Question
{
public:
	vector<pair<int, int>> run(vector<pair<int, int>>& intervals)
	{
		if (intervals.size() < 2) return intervals;
		sort(intervals.begin(), intervals.end());
		vector<pair<int, int>> ret;
		pair<int, int> tmp = intervals[0];
		for (int i = 1; i < intervals.size(); ++i)
		{
			if (tmp.second >= intervals[i].first)
				tmp.second = max(tmp.second, intervals[i].second);
			else
			{
				ret.push_back(tmp);
				tmp = intervals[i];
			}
		}
		ret.push_back(tmp);
		return ret;
	}
};
// 比较简短，没有问很多技术问题，做完题讲了下思路就结束了
// 跟HR聊了下，题做出来了应该问题不大
//

//
//3.14 二面结果
// 通过
// 
//后续
// 一到两天内HRP电话聊一下
//

//
//3.16 HR电话聊
// 聊了目前公司的情况、薪资、生活情况、女朋友、未来规划、期望薪资等
// 
//后续安排综合面试
// 面试官 部门负责人
// 注意个人仪容仪表 提前几分钟入会
// 也会有技术问题
// 
//时间安排
// 2022-03-18 19:00-19:30((UTC+08:00)Beijing)
// 
//时间调整
// 2022-03-17 18:30-19:00((UTC+08:00)Beijing)
//

//
//3.17 技术主管面
// 自我介绍、几个技术问题、职业规划
// 团队中最重要的因素、带领团队的方式
// 讨论问题
// 部门业务、技术难点、物联网、网络安全
// 期望薪资、什么时间能到岗
//
//总结
// 主管亲和力很高，整个流程很自然，也讲了很多关于部门的情况，体验很好
//

//
//3.18 提交资料
// 综面通过
// 
//整理资料提交
// 身份证、毕业证、学位证、四六级、流水证明
// 签署背调和保密协议
// 
//下周一谈薪
// 因为疫情，谈薪搁置两天，暂定周三
// 
//流程真长啊，都半个多月了，不知道一个月能不能确定下来
//

//
//3.23 谈薪
// 之前的流水不太规范，吃了点亏
// 跟预期差了一些，基本不可谈
// 
//想了想，尝试一下看能不能争取转正编吧
// 接了
// 
//3.24 预计4.7报道
//

//
//3.25 补充信息
// 
//审批流程
// 预计周一发offer
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
	vector<pair<int, int>> adj[101];
	//把输入转为邻接表
	for (auto time : times)
		adj[time[0]].push_back({ time[2],time[1] });
	//广度优先搜索
	vector<int> memo(n + 1, INT_MAX);
	queue<int> q;
	q.push(k);
	memo[k] = 0;
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();
		for (auto edge : adj[cur])
		{
			int delay = edge.first;
			int next = edge.second;
			if (memo[next] > memo[cur] + delay)
			{
				memo[next] = memo[cur] + delay;
				q.push(next);
			}
		}
	}
	int ret_bfs = INT_MIN;
	for (int i = 1; i <= n; ++i)
		ret_bfs = max(ret_bfs, memo[i]);
	return ret_bfs == INT_MAX ? -1 : ret_bfs;
}

//搜索单词（medium） /problems/word-search/
class word_search {
public:
	bool exist(vector<vector<char>>& board, string word) {
		int m = board.size();
		int n = board[0].size();

		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
				if (dfs(i, j, m, n, board, word, 0))
					return true;

		return false;
	}

	bool dfs(int i, int j, int m, int n,
		vector<vector<char>>& board,
		const string& word,
		int len)
	{
		if (word[len] == '\0')
			return true;
		if (i < 0 || i >= m || j < 0 || j >= n
			|| len >= word.size() || word[len] != board[i][j])
			return false;
		bool ret = false;
		char tmp = board[i][j];
		board[i][j] = '*';

		ret = dfs(i - 1, j, m, n, board, word, len + 1)
			|| dfs(i + 1, j, m, n, board, word, len + 1)
			|| dfs(i, j - 1, m, n, board, word, len + 1)
			|| dfs(i, j + 1, m, n, board, word, len + 1);

		board[i][j] = tmp;
		return ret;
	}
};

//最大数（medium） /problems/largest-number
class largest_number {
public:
	struct string_cmp {
		bool operator()(const string& a, const string& b)
		{
			//排序巧妙解决了哪个放前面更大，还避免了有0时的默认比较错误
			return a + b < b + a;
		}
	};
	string largestNumber(vector<int>& nums) {
		priority_queue<string, vector<string>, string_cmp> q;
		for (auto num : nums)
			q.push(to_string(num));
		string ret;
		while (!q.empty())
		{
			ret += q.top();
			q.pop();
		}
		//把前面多余的0去除，针对全0情况
		while (ret[0] == '0' && ret.size() > 1)
			ret = ret.substr(1);
		return ret;
	}
};

//矩形面积（medium） /problems/rectangle-area
class rectangle_area {
public:
	bool CheckOverlap(int rec1L, int rec1D, int rec1R, int rec1T,
		int rec2L, int rec2D, int rec2R, int rec2T)
	{
		return (min(rec1R, rec2R) > max(rec1L, rec2L) && min(rec1T, rec2T) > max(rec1D, rec2D));
	}

	int computeArea(int rec1L, int rec1D, int rec1R, int rec1T,
		int rec2L, int rec2D, int rec2R, int rec2T)
	{

		int rec1Area = (rec1R - rec1L) * (rec1T - rec1D);
		int rec2Area = (rec2R - rec2L) * (rec2T - rec2D);

		bool f = CheckOverlap(rec1L, rec1D, rec1R, rec1T,
			rec2L, rec2D, rec2R, rec2T);

		if (!f) return rec1Area + rec2Area;

		int h = min(rec1T, rec2T) - max(rec1D, rec2D);
		int w = min(rec1R, rec2R) - max(rec1L, rec2L);

		return rec1Area + rec2Area - h * w;
	}
};

//根据字符出现频率排序（medium） /problems/sort-characters-by-frequency
class sort_char_by_frequency {
public:
	using pair_type = pair<char, int>;
	struct pair_cmp {
		bool operator()(const pair_type& a, const pair_type& b)
		{
			return a.second < b.second;
		}
	};
	string frequencySort(string s) {
		unordered_map<char, int> memo;
		for (auto c : s)
			memo[c]++;
		priority_queue<pair_type, vector<pair_type>, pair_cmp> q;
		for (auto pair : memo)
			q.push(pair);
		string ret;
		while (!q.empty())
		{
			pair_type top = q.top();
			q.pop();
			for (int i = 0; i < top.second; ++i)
				ret += top.first;
		}
		return ret;
	}
	//更巧妙的写法，不用自己写比较函数
	string smart(string s)
	{
		unordered_map<char, int> freq;           //for frequency of characters
		priority_queue<pair<int, char>> maxheap; //maxheap according to frequency of characters
		for (char c : s)
			freq[c]++;
		for (auto it : freq)
			maxheap.push({ it.second,it.first }); //heap will be constructed on the basis of frequency
		s = "";
		while (!maxheap.empty()) {
			s += string(maxheap.top().first, maxheap.top().second); //frequency times the character
			maxheap.pop();
		}
		return s;
	}
};

//基本计算器（medium） /problems/basic-calculator-ii
class basic_calculator {
public:
	int calculate(string s) {
		if (s.empty()) return 0;
		vector<int> cal;
		char pre_op = '+';
		int cur_num = 0;
		for (int i = 0; i < s.size(); ++i)
		{
			if (isdigit(s[i]))
				cur_num = 10 * cur_num + (s[i] - '0');
			//不是数字和空格，也就是操作符号，或者到结尾了，判断上一个操作符是什么
			if (!isdigit(s[i]) && !isspace(s[i]) || i == s.size() - 1)
			{
				if (pre_op == '+')
					cal.push_back(cur_num);
				if (pre_op == '-')
					cal.push_back(-cur_num);
				if (pre_op == '*')
				{
					int top = cal.back();
					cal.pop_back();
					cal.push_back(top * cur_num);
				}
				if (pre_op == '/')
				{
					int top = cal.back();
					cal.pop_back();
					cal.push_back(top / cur_num);
				}
				//计算一次后清零，记录本次操作符
				cur_num = 0;
				pre_op = s[i];
			}
		}
		//剩下的数字相加即可（减法已经处理成负号）
		int ret = 0;
		for (auto num : cal)
			ret += num;
		return ret;
	}
};

//岛屿数量（medium） /problems/number-of-islands
class islands_number {
public:
	int numIslands(vector<vector<char>>& grid) {
		int count = 0;
		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid[0].size(); j++) {
				if (grid[i][j] == '1') {
					dfs(grid, i, j);
					count++;
				}
			}
		}
		return count;
	}
	void dfs(vector<vector<char>>& grid, int i, int j) {
		if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] == '0')
			return;
		// set to 0 (visited)
		grid[i][j] = '0';
		// search surrounding cells at horizontal/vertical
		dfs(grid, i + 1, j);
		dfs(grid, i, j + 1);
		dfs(grid, i - 1, j);
		dfs(grid, i, j - 1);
	}
};

//三数之和（medium） /problems/3sum
class three_sum {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		vector<vector<int>> ret;
		int n = nums.size();
		sort(nums.begin(), nums.end());
		for (int index1 = 0; index1 + 2 < n/* 后面还有两个索引，空出来 */; ++index1)
		{
			if (index1 > 0 && nums[index1] == nums[index1 - 1])
				continue;//去重左边部分
			int index2 = index1 + 1, index3 = n - 1;
			while (index2 < index3)
			{
				int sum = nums[index1] + nums[index2] + nums[index3];
				if (sum == 0)
				{
					ret.push_back({ nums[index1],nums[index2],nums[index3] });
					//去重右边部分
					--index3;
					while ((index2 < index3) && (nums[index3] == nums[index3 + 1])) --index3;
				}
				else if (sum < 0)//和太小，说明左边的太小，后移
					++index2;
				else //和太大，说明右边太大，前移
					--index3;
			}
		}

		return ret;
	}
};

//排列序列（hard） /problems/permutation-sequence
class permutation_sequence {
public:
	string getPermutation(int n, int k) {
		//准备1到n的数组（或字符串）
		// 假设 n = 4 , k = 15
		// 1到4排列有24种，以第一个数字为例
		// 1到4每个数字开头分别有6种，也就是(n-1)!种
		//每个数字的选择
		// 第15个数字，除以每个数字开头6种，结果2
		// 也就是字符串中索引为2的数字'3'
		// 确定第一个数字为3，其余数字剩 '124'
		// 第二个数字选择是3个数字中选择，总共6种，每个数字开头分别2种
		// 之前15与6除找到第一个数字，取模结果3，即剩下6种里再取第3个
		// 第3个数字，除以每个数字2种，结果1
		// 也就是字符串中索引为1的数字'2'，当前排列 '32'
		// 确认第二个数字后，其余数字剩 '14'
		// 第三个数字是2个数字中选择，总共2种，每个数字开头分别1种
		// 3与2取模结果1，也就是剩下两种取第1个
		// '321' 剩余 '4'
		// 加上剩余一个字符 '3214'
		//
		if (n == 1) return "1";
		//准备好所有阶乘数
		vector<int> fac(n + 1, 1);
		for (int i = 1; i <= n; ++i)
			fac[i] = i * fac[i - 1];
		//结果与备选字符
		string ret;
		vector<int> numbers;
		for (int i = 1; i <= n; ++i)
			numbers.push_back(i);
		//递归选择每个数字
		setPerm(numbers, ret, n, k, fac);
		return ret;
	}
	void setPerm(vector<int>& numbers, string& ret, int n, int k, vector<int>& fac)
	{
		if (n == 1)
		{
			//只剩最后一个了，直接加
			ret += to_string(numbers.back());
			return;
		}
		//每个字符开头有(n-1)!种，用k除以它去找
		int index = k / fac[n - 1];
		//如果刚好整除，则应该是第0个
		if (k % fac[n - 1] == 0)
			--index;
		//拼接当前数字并从候选中去掉
		ret += to_string(numbers[index]);
		numbers.erase(numbers.begin() + index);
		//下一个选择时，就是从n-1个数字中求第选完当前数字后的第k个
		k -= fac[n - 1] * index;
		//递归这个逻辑
		setPerm(numbers, ret, n - 1, k, fac);
	}
};

//烂橘子（medium） /problems/rotting-oranges/ 
class rott_orange {
public:
	int orangesRotting(vector<vector<int>>& grid) {
		//由于可能刚开始存在多个烂橘子，所以应该是从所有烂橘子开始广度优先搜索，而不是dfs
		int m = grid.size();
		int n = grid[0].size();
		//bfs使用队列
		queue<pair<int, int>> q;
		//烂橘子入队准备搜索，并统计新鲜橘子数
		int fresh = 0;
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (grid[i][j] == 2)
					q.push({ i,j });
				if (grid[i][j] == 1)
					++fresh;
			}
		}
		//开始搜索
		vector<int> dir = { -1,0,1,0,-1 };//用于四个方向扩散的辅助数组
		int ret = -1;//第一次搜索是原本存在的烂橘子，+1后是0开始
		while (!q.empty())
		{
			int size = q.size();
			while (size-- > 0)
			{
				auto rott = q.front();
				q.pop();
				//往四个方向腐烂
				for (int i = 0; i < 4; ++i)
				{
					int x = rott.first + dir[i];
					int y = rott.second + dir[i + 1];
					//在范围内且为新鲜橘子才继续扩散
					if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 1)
					{
						grid[x][y] = 2;
						q.push({ x,y });
						--fresh;//记录被影响的橘子
					}
				}
			}
			++ret;
		}
		//如果还有新鲜橘子，则是永远不会被影响
		if (fresh > 0) return -1;
		//没有橘子，返回0
		if (ret == -1) return 0;
		return ret;
	}
};

//最小绝对差（easy） /problems/minimum-absolute-difference
class min_abs_diff {
public:
	vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
		vector<vector<int>> ret;
		if (arr.size() < 2) return ret;
		sort(arr.begin(), arr.end());
		int min_diff = INT_MAX;
		for (int i = 0; i < arr.size() - 1; ++i)
			min_diff = min(min_diff, abs(arr[i + 1] - arr[i]));
		for (int i = 0; i < arr.size() - 1; ++i)
			if (abs(arr[i + 1] - arr[i]) == min_diff)
				ret.push_back({ arr[i],arr[i + 1] });
		return ret;
	}
};

//外观数列（medium） /problems/count-and-say
class count_and_say {
public:
	string countAndSay(int n) {
		if (n == 0) return "";
		string ret = "1";
		while (--n)
		{
			string cur;
			for (int i = 0; i < ret.size(); ++i)
			{
				int count = 1;
				while ((i + 1 < ret.size()) && (ret[i] == ret[i + 1]))
				{
					++count;
					++i;
				}
				cur += to_string(count) + ret[i];
			}
			ret = cur;
		}
		return ret;
	}
};

//最大整除子集（medium） /problems/largest-divisible-subset
class largest_divisible_subset {
public:
	vector<int> largestDivisibleSubset(vector<int>& nums) {
		//先排序
		sort(nums.begin(), nums.end());
		int n = nums.size(), max_i = 0;
		vector<int> dp(n, 1);//记录以第i个数字结尾的最大子集大小，默认为1是因为至少自己可以作为子集
		vector<int> pre(n, -1);//记录以第i个数组结尾的子集的前一个数字索引，以便重建最大子集
		vector<int> ret;
		//以每个数字为结尾，计算符合结果的最大情况
		for (int i = 1; i < n; ++i)
		{
			for (int j = 0; j < i; ++j)
				if (nums[i] % nums[j] == 0 && dp[i] < dp[j] + 1)
					dp[i] = dp[j] + 1, pre[i] = j;
			if (dp[i] > dp[max_i]) max_i = i;
		}
		//利用pre记录的前置索引弄出子集
		while (max_i >= 0)
		{
			ret.push_back(nums[max_i]);
			max_i = pre[max_i];
		}
		return ret;
	}
};

//省份数量（medium） /problems/number-of-provinces
class provinces_number {
public:
	int findCircleNum(vector<vector<int>>& isConnected) {
		int n = isConnected.size();
		//二维邻接矩阵表示的图，以对角线分割两边是一样的，所以只用一维记录即可
		vector<bool> visited(n, false);
		int group = 0;
		for (int i = 0; i < n; ++i)
		{
			if (visited[i] == false)
			{
				++group;
				dfs(i, isConnected, visited);
			}
		}
		return group;
	}
	void dfs(int i, vector<vector<int>>& isConnected, vector<bool>& visited)
	{
		visited[i] = true;
		for (int j = 0; j < visited.size(); ++j)
			if (i != j && isConnected[i][j] && !visited[j])
				dfs(j, isConnected, visited);
	}
};

//合并有序数组（easy） /problems/merge-sorted-array
class merge_sorted_array {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		int i = m - 1, j = n - 1, target = m + n - 1;
		while (i >= 0 && j >= 0)
			nums1[target--] = nums1[i] > nums2[j] ? nums1[i--] : nums2[j--];
		while (i >= 0)
			nums1[target--] = nums1[i--];
		while (j >= 0)
			nums1[target--] = nums2[j--];
	}
};

//第N个泰波那契数（easy） /problems/n-th-tribonacci-number
class nth_tribonacci {
public:
	int tribonacci(int n) {
		vector<int> trib = { 0,1,1 };
		if (n < 3) return trib[n];
		for (int i = 3; i <= n; ++i)
			trib.push_back(trib[i - 3] + trib[i - 2] + trib[i - 1]);
		return trib[n];
	}
};

//剑指offer45 把数组排成最小数（medium） 
//https://leetcode-cn.com/problems/ba-shu-zu-pai-cheng-zui-xiao-de-shu-lcof/
class sort_arr_to_min_num {
public:
	struct str_cmp {
		bool operator()(const string& a, const string& b)
		{
			return a + b > b + a;
		}
	};
	string minNumber(vector<int>& nums) {
		priority_queue<string, vector<string>, str_cmp> q;
		for (auto& num : nums)
			q.push(to_string(num));
		string ret;
		while (!q.empty())
		{
			ret += q.top();
			q.pop();
		}
		return ret;
	}
};

//所有蚂蚁掉落的最后时刻（medium） /problems/last-moment-before-all-ants-fall-out-of-a-plank
class last_momoent {
public:
	int getLastMoment(int n, vector<int>& left, vector<int>& right) {
		// The one that is farthest from the left end, but desires to go in the left
		// direction, will be the last one to go off of the plank from the left side.
		int maxLeft = left.empty() ? 0 : *max_element(left.begin(), left.end());

		// Similarly,
		// The one that is farthest from the right end, but desires to go in the right
		// direction, will be the last one to go off of the plank from the right side.
		int minRight = right.empty() ? n : *min_element(right.begin(), right.end());

		// The one among above two would be the last one to off of the plank among all.
		return max(maxLeft, n - minRight);
	}
};

//压缩字符串（medium） /problems/string-compression
class compress_string {
public:
	int compress(vector<char>& chars) {
		if (chars.size() == 1) return 1;
		int target = 0, count = 0, index = 0;
		while (index < chars.size())
		{
			chars[target] = chars[index];
			count = 0;
			while (index < chars.size() && chars[index] == chars[target])
			{
				++index;
				++count;
			}
			if (count == 1)
				++target;
			else
			{
				string str = to_string(count);
				for (auto ch : str)
					chars[++target] = ch;
				++target;
			}
		}
		return target;
	}
};

//解码字符串（medium） /problems/decode-string
class decode_string {
public:
	string decodeString(string s) {
		int pos = 0;
		return helper(s, pos);
	}
	string helper(string& s, int& pos)
	{
		int num = 0;
		string ret;
		for (; pos < s.size(); ++pos)
		{
			char cur = s[pos];
			if (isdigit(cur))
				num = num * 10 + (cur - '0');
			else if (cur == '[')
			{
				string tmp = helper(s, ++pos);
				while (num-- > 0) ret += tmp;
				num = 0;
			}
			else if (cur == ']')
				return ret;
			else
				ret += cur;
		}
		return ret;
	}
};

//根据身高重建序列（medium） /problems/queue-reconstruction-by-height
class queue_rector_by_height {
public:
	vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
		auto comp = [](const vector<int>& p1, vector<int>& p2)
		{ return p1[0] > p2[0] || (p1[0] == p2[0] && p1[1] < p2[1]); };
		sort(people.begin(), people.end(), comp);
		vector<vector<int>> res;
		for (auto& p : people)
			res.insert(res.begin() + p[1], p);
		return res;
	}
};

//判断子序列（easy） /problems/is-subsequence
class sub_seq {
public:
	bool isSubsequence(string s, string t) {
		int i = 0, j = 0;
		while (i < s.size() && j < t.size())
		{
			if (s[i] == t[j])
				++i, ++j;
			else
				++j;
		}
		return i == s.size();
	}
};

//基本计算器（hard） /problems/basic-calculator
class calc {
public:
	int calculate(string s) {
		//递归方式
		int pos = 0;
		return eval(s, pos);
	}
	int eval(string& s, int& pos)
	{
		int ret = 0;
		int sign = 1;
		for (; pos < s.size(); ++pos)
		{
			if (isdigit(s[pos]))
			{
				long num = 0;
				while (pos < s.size() && isdigit(s[pos]))
					num = num * 10 + s[pos++] - '0';
				pos--;
				ret += sign * num;
				sign = 1;
			}
			else if (s[pos] == '-')
				sign = -1;
			else if (s[pos] == '(')
			{
				ret += sign * eval(s, ++pos);
				sign = 1;
			}
			else if (s[pos] == ')')
				return ret;
		}
		return ret;
	}
	//栈方式
	int calculate_stack(string s) {
		stack<pair<int, int>> st; // pair(prev_calc_value , sign before next bracket () )

		long long int sum = 0;
		int sign = +1;

		for (int i = 0; i < s.size(); ++i)
		{
			char ch = s[i];

			if (isdigit(ch))
			{
				long long int num = 0;
				while (i < s.size() and isdigit(s[i]))
				{
					num = (num * 10) + s[i] - '0';
					i++;
				}
				i--; // as for loop also increase i , so if we don't decrease i here a sign will be skipped
				sum += (num * sign);
				sign = +1; // reseting sign
			}
			else if (ch == '(')
			{
				// Saving current state of (sum , sign) in stack
				st.push(make_pair(sum, sign));

				// Reseting sum and sign for inner bracket calculation
				sum = 0;
				sign = +1;
			}
			else if (ch == ')')
			{
				sum = st.top().first + (st.top().second * sum);
				st.pop();
			}
			else if (ch == '-')
			{
				// toggle sign
				sign = (-1 * sign);
			}
		}
		return sum;
	}
};

//学生出勤记录（easy） /problems/student-attendance-record-i
class student_attend_record {
public:
	bool checkRecord(string s) {
		int a = 0, l = 0;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == 'A') a++;
			if (s[i] == 'L') l++;
			else l = 0;
			if (a >= 2 || l > 2) return false;
		}
		return true;
	}
};

//更长的连续段（easy） /problems/longer-contiguous-segments-of-ones-than-zeros
class longer_ones_than_zeros {
public:
	bool checkZeroOnes(string s) {
		int ones = 0, zeros = 0;
		int conti_ones = 0, conti_zeros = 0;
		for (int i = 0; i < s.size(); ++i)
		{
			if (s[i] == '0')
			{
				conti_ones = max(conti_ones, ones);
				ones = 0;
				++zeros;
			}
			else
			{
				conti_zeros = max(conti_zeros, zeros);
				zeros = 0;
				++ones;
			}
		}
		return conti_ones > conti_zeros;
	}
};

//全排列（medium） /problems/permutations
class perm {
public:
	vector<vector<int>> permute(vector<int>& nums) {
		vector<vector<int>> ret;
		impl(nums, 0, ret);
		return ret;
	}
	void impl(vector<int>& nums, int i, vector<vector<int>>& ret)
	{
		if (i == nums.size() - 1)
			ret.push_back(nums);
		for (int j = i; j < nums.size(); ++j)
		{
			swap(nums[i], nums[j]);
			impl(nums, i + 1, ret);
			swap(nums[i], nums[j]);
		}
	}
};

//跳跃游戏（medium） /problems/jump-game-iii
class jump_game_iii {
public:
	bool canReach(vector<int>& arr, int start) {
		vector<bool> visited(arr.size(), false);
		return dfs(arr, start, visited);
	}
	bool dfs(vector<int>& arr, int i, vector<bool>& visited)
	{
		if (i < 0 || i >= arr.size() || visited[i])
			return false;
		if (arr[i] == 0) return true;
		visited[i] = true;
		return dfs(arr, i + arr[i], visited)
			|| dfs(arr, i - arr[i], visited);
	}
};

//分割数组为连续子串（medium） /problems/split-array-into-consecutive-subsequences
class split_array_into_subseq {
public:
	//我使用了一个贪心算法。
	//	left 是一个 hashmap，left[i] 计算我还没有放置的 i 的数量。
	//	end 是一个 hashmap，end[i] 计算以数字 i 结尾的连续子序列的数量
	//	然后我尝试将数字一一拆分。
	//	如果我既不能在现有连续子序列的末尾添加一个数字，也不能在左边找到两个后续数字，我返回 False
	//该解决方案的关键点是，如果存在以 x-1 结尾的有效子序列，
	// 则将当前 x 放在子序列的末尾总是比创建以 x 开头的新子序列更好/更低的风险，因为它的长度至少为 3。
	//我认为您必须首先意识到每个数字可以是给定迭代点的序列的开头或结尾。
	// 这个解决方案的另一个微妙之处是证明附加到先前的序列总是比创建新序列更好。
	// 考虑问题 [1,2,3,4,5,5,6,7] 以及如何优先创建子序列而不是附加会导致问题。
	bool isPossible(vector<int>& A) {
		unordered_map<int, int> left, end;
		for (int i : A) {
			left[i]++;
		}
		for (int i : A) {
			if (left[i] == 0) continue;
			left[i]--;
			if (end[i - 1] > 0) {
				end[i - 1]--;
				end[i]++;
			}
			else if (left[i + 1] > 0 && left[i + 2] > 0) {
				left[i + 1]--;
				left[i + 2]--;
				end[i + 2]++;
			}
			else {
				return false;
			}
		}
		return true;
	}
};

//排序数组（medium） /problems/sort-an-array
class sort_array {
public:
	vector<int> sortArray(vector<int>& nums) {
		quick_sort(nums, 0, nums.size() - 1);
		return nums;
	}
	void quick_sort(vector<int>& arr, int start, int end)
	{
		if (start >= end)
			return;
		int pivot = partition(arr, start, end);
		if (pivot > start)
			quick_sort(arr, start, pivot - 1);
		if (pivot < end)
			quick_sort(arr, pivot + 1, end);
	}
	int partition(vector<int>& arr, int start, int end)
	{
		int q = start;
		for (int i = start; i < end; ++i)
		{
			if (arr[i] < arr[end])
			{
				swap(arr[i], arr[q]);
				++q;
			}
		}
		swap(arr[q], arr[end]);
		return q;
	}
};

//最大子序列和（easy） /problems/maximum-subarray
class max_subarray {
public:
	int maxSubArray(vector<int>& nums) {
		//暴力解
		int n = size(nums), ans = INT_MIN;
		for (int i = 0; i < n; i++)
			for (int j = i, curSum = 0; j < n; j++)
				curSum += nums[j],
				ans = max(ans, curSum);
		return ans;
		//dp
		//记录以i结尾的最大子数组和
		vector<int> dp(nums);
		for (int i = 1; i < size(nums); i++)
			dp[i] = max(nums[i], nums[i] + dp[i - 1]);
		return *max_element(begin(dp), end(dp));
		//kadane
		int curMax = 0, maxTillNow = INT_MIN;
		for (auto c : nums)
			curMax = max(c, curMax + c),
			maxTillNow = max(maxTillNow, curMax);
		return maxTillNow;
	}
};

//最接近的三数之和（medium） /problems/3sum-closest
class three_sum_closest {
public:
	int threeSumClosest(vector<int>& nums, int target) {
		sort(nums.begin(), nums.end());
		int n = nums.size(), ans = nums[0] + nums[1] + nums[2];
		for (int i = 0; i < n - 2; ++i) {
			int l = i + 1, r = n - 1;
			while (l < r) {
				int sum3 = nums[i] + nums[l] + nums[r];
				if (abs(ans - target) > abs(sum3 - target)) // Update better ans
					ans = sum3;
				if (sum3 == target) break;
				if (sum3 > target)
					--r; // Sum3 is greater than the target, to minimize the difference, we have to decrease our sum3
				else
					++l; // Sum3 is lesser than the target, to minimize the difference, we have to increase our sum3
			}
		}
		return ans;
	}
};

//连续子数组的和（medium) /problems/continuous-subarray-sum
class check_subarray_sum {
public:
	bool checkSubarraySum(vector<int>& nums, int k) {
		if (nums.size() < 2)
			return false;

		//使用map记录到索引i的和的模
		unordered_map<int, int> umap;
		umap[0] = -1;
		int sum = 0;
		for (int i = 0; i < nums.size(); ++i)
		{
			sum += nums[i];
			sum %= k;
			//每次取模，之后看有没有模相同的，有说明一定有整除的
			if (umap.find(sum) != umap.end())
			{
				if (i - umap[sum] > 1)
					return true;
			}
			else
				umap[sum] = i;
		}
		return false;
#if 0
		//不使用map，但使用一个pre做延迟检查，以便子序列长度至少为2
		int n = nums.size(), sum = 0, pre = 0;
		unordered_set<int> modk;
		for (int i = 0; i < n; ++i) {
			sum += nums[i];
			int mod = k == 0 ? sum : sum % k;
			if (modk.count(mod)) return true;
			modk.insert(pre);
			pre = mod;
		}
		return false;
#endif
	}
};

//只有两个键的键盘（medium） /problems/2-keys-keyboard
class two_keys_board {
public:
	int minSteps(int n) {
		//数学解法，素数分解
		int ans = 0, d = 2;
		while (n > 1) {
			while (n % d == 0) {
				ans += d;
				n /= d;
			}
			d++;
		}
		return ans;
	}
	//dp解法
	// dp vector to store <step,value> result for using in future
	int dp[1001][1001];

	int minKeyPress(int step, int value, int copy, int& n)
	{
		// impossible case when step>n or value>n, so return INT_MAX
		if (step > n || value > n) return INT_MAX;

		// reached target value and so return step 
		if (value == n) return step;

		// return recalculated value
		if (dp[step][value] != -1) return dp[step][value];

		// return min step to reach the target value
		// there are 2 choices: paste copied value with current value => 1 step
		// copy current value and paste it with itself => 2 step
		return dp[step][value] = min(minKeyPress(step + 1, value + copy, copy, n), minKeyPress(step + 2, 2 * value, value, n));
	}

	int minSteps_dp(int n) {

		// base case : n==1 no steps needed
		if (n == 1) return 0;

		memset(dp, -1, sizeof(dp));

		// start with value 1 and copy 1 and intial step 1 (assuming we already copied the intial value 'A')
		return minKeyPress(1, 1, 1, n);
	}
};

//完成所有工作最短时间（hard） /problems/find-minimum-time-to-finish-all-jobs
class min_time_finish_jobs {
public:
	//这是一个NP完全的多背包问题。因此，严格约束(k <= 12)。
	//	所以，我们需要做完整的搜索，但我们可以加快一点：
	//	跟踪当前的最佳结果并使用它进行修剪。
	//	如果两个或多个工人的工作时间相同，我们只需要考虑其中一个。
	//	最后的优化有很大帮助，我们可以只使用一个哈希集来跟踪工作时间。
	//	更新。我最初进行了排序，但后来被删除，因为没有它的解决方案被接受了。
	//	为了更有效地剪枝，我们可以将作业按降序排序，并计算一个贪心结果，这应该是一个很好的开始。
	int worker[12] = {}, res = 0;
	int dfs(vector<int>& jobs, int i, int k, int cur) {
		if (cur >= res)
			return res;
		if (i == jobs.size())
			return res = cur;
		unordered_set<int> workTime;
		for (auto j = 0; j < k; ++j) {
			if (!workTime.insert(worker[j]).second)
				continue;
			worker[j] += jobs[i];
			dfs(jobs, i + 1, k, max(cur, worker[j]));
			worker[j] -= jobs[i];
		}
		return res;
	}
	int minimumTimeRequired(vector<int>& jobs, int k) {
		if (k == jobs.size())
			return *max_element(begin(jobs), end(jobs));
		sort(begin(jobs), end(jobs), greater<int>());
		for (int i = 0; i < jobs.size(); i += k)
			res += jobs[i];
		return dfs(jobs, 0, k, 0);
	}
};

//连续整数求和（hard） /problems/consecutive-numbers-sum
class consecutive_num_sum {
public:
	int consecutiveNumbersSum(int N) {
		//思考过程是这样的
		// 给定一个数字 N，我们可以把它写成 2 个数字、3 个数字、4 个数字等的总和。让我们假设这个系列中的第一个数字是 x。
		// 因此，我们应该有
		//	x + (x + 1) + (x + 2) + ... + k 项 = N
		//	kx + k * (k - 1) / 2 = N 意味着
		//	kx = N - k * (k - 1) / 2
		//	因此，我们可以计算每个 k 值的 RHS，如果它是 k 的倍数，那么我们可以使用从 x 开始的 k 项构造 N 的总和。
		//	现在，问题出现了，直到我们应该循环获取 k 的值是多少？这很简单。在最坏的情况下，RHS 应该大于 0。即
		//	N - k * (k - 1) / 2 > 0 这意味着
		//	k * (k - 1) < 2N 可以近似为
		//	k * k < 2N ==> k < sqrt(2N)
		//	因此算法的整体复杂度为 O(sqrt(N))
		//	PS：OJ 期望答案比可能方式的数量大 1，因为它认为 N 被写为 N 本身。
		//  这很令人困惑，因为他们要求连续整数的总和，这意味着至少 2 个数字。但是为了取悦OJ，我们应该从1开始数。
		int count = 1;
		for (int k = 2; k < sqrt(2 * N); k++) {
			if ((N - (k * (k - 1) / 2)) % k == 0) count++;
		}
		return count;
	}
};

//单词接龙（hard） /problems/word-ladder
class word_ladder {
public:
	int ladderLength(string beginWord, string endWord, vector<string>& wordList) {

	}
};

//找出偶数中包含元音的最长子串（medium） /problems/find-the-longest-substring-containing-vowels-in-even-counts/
class longest_substring_contain_vowels {
public:

	//我们不需要知道确切的计数，我们只需要一个指示元音是偶数还是奇数的标志。因此，我们可以使用位掩码跟踪每个元音的状态。由于我们在英文字母表中只有 5 个元音，我们将有 32 种可能的组合。
	//	现在，如果我们的掩码为零，那么我们的字符串只包含偶数元音。此外，如果索引 i 和 j 的掩码相同，则子字符串[i + 1, j] 的掩码必须为零。因此，子串[i + 1, j] 也只包含偶元音。
	//	算法
	//	当我们遍历我们的字符串时，我们更新掩码，并跟踪每个掩码组合的最小索引。如果我们稍后在字符串中遇到相同的掩码，这意味着最小（不包括）和当前（包括）索引之间的字符串符合问题标准。
	//	换句话说，我们需要找到每个掩码组合的第一个和最后一个索引之间的最大距离。
	//	请注意，对于零掩码（所有元音的计数都是偶数），第一个索引是 '-1' - 所以我们从一开始就包含字符串。
	static constexpr char c_m[26] = { 1,0,0,0,2,0,0,0,4,0,0,0,0,0,8,0,0,0,0,0,16,0,0,0,0,0 };
	int findTheLongestSubstring(string s) {
		int mask = 0, res = 0;
		vector<int> m(32, -1);
		for (int i = 0; i < s.size(); ++i) {
			mask ^= c_m[s[i] - 'a'];
			if (mask != 0 && m[mask] == -1)
				m[mask] = i;
			res = max(res, i - m[mask]);
		}
		return res;

		//会TLE但易于理解的方法
		unordered_map<char, int>cnt;
		unordered_map<string, int>mp; mp["00000"] = -1;
		vector<char>vowels{ 'a','e','i','o','u' };
		int ans = 0; string temp = "";
		for (int i = 0; i < s.length(); i++)
		{
			char x = s[i]; temp = "";
			cnt[x]++;
			for (int j = 0; j < 5; j++) temp += to_string(cnt[vowels[j]] % 2);
			if (mp.find(temp) != mp.end()) ans = max(ans, i - mp[temp]);
			else mp[temp] = i;
		}
		return ans;
	}
};

//移除K个数字（medium） /problems/remove-k-digits
class remove_K_digit {
public:
	//input 1432219 3 output 1219
	string removeKdigits(string num, int k) {
		string ans = "";                                         // treat ans as a stack in below for loop

		for (char c : num) {
			while (ans.length() && ans.back() > c && k) {
				ans.pop_back();                                  // make sure digits in ans are in ascending order
				k--;                                             // remove one char
			}

			if (ans.length() || c != '0') { ans.push_back(c); }  // can't have leading '0'
		}

		while (ans.length() && k--) { ans.pop_back(); }          // make sure remove k digits in total

		return ans.empty() ? "0" : ans;
	}
};

//K进制表示各位总和（easy） /problems/sum-of-digits-in-base-k
class sum_digits_in_base_k {
public:
	int sumBase(int n, int k) {
		int sum = 0;
		while (n != 0) sum += n % k, n = n / k;
		return sum;
	}
};

//从前序和中序遍历中构建二叉树（medium） /problems/construct-binary-tree-from-preorder-and-inorder-traversal/
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

};
class ctor_binary_tree {
public:
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		if (preorder.empty() || inorder.empty() || preorder.size() != inorder.size())
			return nullptr;
		return build(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
	}
	TreeNode* build(vector<int>& preorder, vector<int>& inorder, int startpre, int endpre, int startin, int endin)
	{
		TreeNode* root = new TreeNode(preorder[startpre]);
		if (startpre == endpre && startin == endin)
			if (preorder[startpre] == inorder[startin])
				return root;
		int root_inorder = startin;
		while (root_inorder < endin && inorder[root_inorder] != root->val)
			++root_inorder;
		if (root_inorder == endin && inorder[root_inorder] != root->val)
			return nullptr;
		int leftlen = root_inorder - startin;
		int leftendpre = startpre + leftlen;
		if (leftlen > 0)
			root->left = build(preorder, inorder, startpre + 1, leftendpre, startin, root_inorder - 1);
		if (leftlen < endpre - startpre)
			root->right = build(preorder, inorder, leftendpre + 1, endpre, root_inorder + 1, endin);
		return root;
	}
};

//最大嵌套深度（easy） /problems/maximum-nesting-depth-of-the-parentheses
class max_depth {
public:
	int maxDepth(string s) {
		int res = 0;
		int depth = 0;
		for (int i = 0; i < s.size(); ++i)
		{
			if (s[i] == '(')
				++depth;
			else if (s[i] == ')')
				--depth;
			res = max(depth, res);
		}
		return res;
	}
};

//相对名次（easy） /problems/relative-ranks
class relative_ranks {
public:
	vector<string> findRelativeRanks(vector<int>& score) {
		priority_queue<pair<int, int>> q;
		for (int i = 0; i < score.size(); ++i)
			q.push({ score[i], i });
		int i = 0;
		vector<string> ret(score.size());
		while (!q.empty())
		{
			ret[q.top().second] = i == 0 ? "Gold Medal" : i == 1 ? "Silver Medal" : i == 2 ? "Bronze Medal" : to_string(i + 1);
			++i;
			q.pop();
		}
		return ret;
	}
};

//盛水的最大容器（medium） /problems/container-with-most-water
class most_water_container {
public:
	int maxArea(vector<int>& height) {
		int water = 0;
		int i = 0, j = height.size() - 1;
		while (i < j) {
			int h = min(height[i], height[j]);
			water = max(water, (j - i) * h);
			while (height[i] <= h && i < j) i++;
			while (height[j] <= h && i < j) j--;
		}
		return water;
	}
};

//数组中第K个最大元素（medium） /problems/kth-largest-element-in-an-array
class kth_largest_element {
public:
	int findKthLargest(vector<int>& nums, int k) {
#if 0
		//排序后遍历k个
		sort(nums.begin(), nums.end());
		return nums[nums.size() - k];
#endif
		//最小堆
		priority_queue<int, vector<int>, greater<int>> q;
		for (auto nums : nums)
		{
			q.push(nums);
			if (q.size() > k) q.pop();//只留k个
		}
		return q.top();
	}
};

//等于K的子数组和（medium） /problems/subarray-sum-equals-k
class subarray_sum_equal_k {
public:
	int subarraySum(vector<int>& nums, int k) {
#if 0
		int count = 0;
		for (int start = 0; start < nums.size(); start++) {
			int sum = 0;
			for (int end = start; end < nums.size(); end++) {
				sum += nums[end];
				if (sum == k)
					count++;
			}
		}
		return count;
#endif 
		unordered_map<int, int> mp;
		int sum = 0, ans = 0;
		mp[sum] = 1;
		for (auto it : nums) {
			sum += it;
			int find = sum - k;
			if (mp.find(find) != mp.end())
				ans += mp[find];
			mp[sum]++;
		}
		return ans;
	}
};

//对角线遍历（medium） /problems/diagonal-traverse
class diagonal_traverse {
public:
	vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
		//分解来做，先只考虑单方向对角线，再隔行反转
		// Check for empty matrices
		if (mat.size() == 0) return vector<int>();

		// Variables to track the size of the matrix
		int N = mat.size();
		int M = mat[0].size();

		// The two arrays as explained in the algorithm
		vector<int> result;
		int k = 0;

		// We have to go over all the elements in the first
		// row and the last column to cover all possible diagonals
		for (int d = 0; d < N + M - 1; d++) {

			// Clear the intermediate array every time we start
			// to process another diagonal
			vector<int> intermediate;

			// We need to figure out the "head" of this diagonal
			// The elements in the first row and the last column
			// are the respective heads.
			int r = d < M ? 0 : d - M + 1;
			int c = d < M ? d : M - 1;

			// Iterate until one of the indices goes out of scope
			// Take note of the index math to go down the diagonal
			while (r < N && c > -1) {

				intermediate.push_back(mat[r][c]);
				++r;
				--c;
			}

			// Reverse even numbered diagonals. The
			// article says we have to reverse odd 
			// numbered articles but here, the numbering
			// is starting from 0 :P
			if (d % 2 == 0) {
				reverse(intermediate.begin(), intermediate.end());
			}

			for (int i = 0; i < intermediate.size(); i++) {
				result.push_back(intermediate[i]);
			}
		}
		return result;
	}
};



//
//机考第三题详情
// 
//最长广播响应
// 某通信网络中有N个网络节点，用1到N标识，网络中节点相互联通，节点间消息传递延迟为一个时间单位（无权有向图）
// 现给定网络节点 link[i] = u,v ，u和v表示网络节点
// 当指定节点发出广播，所有广播节点收到消息后都会在原路回复响应，计算至少需要几个等待时间才能收到所有节点响应
// （到每个节点的最短时间 * 2）
// 
// 注：
// N 范围 [1,1000]
// 连接link长度不超过3000，且 1 < u,v < N
// 网络中任意节点可达
// 
// 输入：
// 5 7 （第一行表示有5个节点，7组节点连接信息）
// 2 1 （从节点2->节点1）
// 2 3
// 1 4
// 2 4
// 4 5
// 3 5
// 3 4
// 2   （从节点2发送广播）
// 
// 输出：
// 4 
//
class longest_broadcast_response
{
public:
	//邻接表
	vector<int> adj[1001];//N范围（如果网络延迟不同，用pair记录权重）
	void run()
	{
		int N, I;//N个节点，I组链接
		while (cin >> N >> I)
		{
			int u, v;//链接两端
			for (int i = 0; i < I; ++i)
			{
				cin >> u >> v;
				adj[u].push_back(v);
			}
			int k;//广播节点
			cin >> k;

			vector<int> memo_dfs(N + 1, INT_MAX);//记录到每个节点的最短时间
			int ret_dfs = INT_MIN;
			dfs(memo_dfs, k, 0);
			for (int i = 1; i <= N; ++i)
				ret_dfs = max(memo_dfs[i], ret_dfs);

			vector<int> memo_bfs(N + 1, INT_MAX);
			int ret_bfs = INT_MIN;
			bfs(memo_bfs, k);
			for (int i = 1; i <= N; ++i)
				ret_bfs = max(memo_bfs[i], ret_bfs);

			cout << "dfs_ret: " << ret_dfs * 2 << endl;
			cout << "bfs_ret: " << ret_bfs * 2 << endl;
		}
	}
private:
	//深度优先搜索方法
	void dfs(vector<int>& memo, int node, int delay)
	{
		//已经比当前记录过的时间更长就没必要再找下去了
		if (delay >= memo[node])
			return;
		//记录到此节点的时间
		memo[node] = delay;
		//从当前节点能够到达的节点依次往深处搜索
		for (auto edge : adj[node])
			dfs(memo, edge, delay + 1);
	}
	//广度优先搜索方法
	void bfs(vector<int>& memo, int node)
	{
		//建立一个队列准备存放当前遍历层节点
		queue<int> q;
		q.push(node);
		//节点自身时间为0
		memo[node] = 0;
		//开始出入队
		while (!q.empty())
		{
			//每个节点出队同时把其后层节点加入队列
			int cur = q.front();
			q.pop();
			for (auto edge : adj[cur])
			{
				//到达时间更长的就不用入队了
				if (memo[edge] > memo[cur] + 1)
				{
					memo[edge] = memo[cur] + 1;
					q.push(edge);
				}
			}
		}
	}
};
//