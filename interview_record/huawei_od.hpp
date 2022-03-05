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
class permutation_sequence{
public:
	string getPermutation(int n, int k) {

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