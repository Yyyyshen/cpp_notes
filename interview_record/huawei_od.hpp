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
//��ΪOD
// �绰��ͨ���˽⵽OD�����ȹ���������ҵ��һ����л���ת����Ҳ�����������
// ��˵ת�����ʲ�����
// 
// ��һ�ֱ��ԣ�������������ϰ������
// �����ϰ�� 
//  https://blog.csdn.net/armstronghappy/article/details/119236183
// ������Ϣ
// a �ϸ��ղ��������÷֣���һ���Ǽ򵥵����С��ÿ����100�֣�
// �ڶ����ѵ�һ��200�֣���һ���ύ���ܷ��أ��ύ����ܿ��ڶ��⣬
// ʱ���ܹ�2.5Сʱ������ʱ�䣬���û�а��������Ȱ�ǰ����������
// b ţ����leetcode��̵�ʱ��������������úõģ�����ʵ�ʿ��Թ�����Ҫ�Լ�д��
// ������ϰţ������ʱ���ÿ���ģʽ������ҵ�����߿������ã�������ģʽ����Ҫ�Լ�д�������
// 
//ˢ�˼�����֮��о�����ʱ��׼��50���е�����
// ��������˵����ֱ��ˢţ�͵Ļ�Ϊ������
// https://www.nowcoder.com/ta/huawei
// 
//�ؼ���
// ˢ�� ���ÿ���ģʽ �������
//

//
//3.2 ���������
// ��¼
// 
//��1���������
// ����֮������֣��������� A = B + 2C
// �仯������������˭��C��������������ֱ�����һ��
// AC 100%
// 
//��2������������
// �������������ͣ���ͬ��˼·����
// ��ͬ���Ǵ���ĿֻҪû����ȫ�պϾͲ���Ϸ�����
// ���� ([)] 
// �Ϸ� ([]{[]}) �Ϸ���Ƕ�����3
// �о�˼·�ǶԵģ�������Щ�����벻��
// AC 70%
// 
//��3�����������Ӧ
// ����һ���������һ������ͼ
// �ٸ�һ���ڵ�ֵ
// �ӽڵ㷢�͹㲥�����յ����нڵ�ظ��������Ӧʱ��
// ����
// 5 7 ������ڵ� �������ݣ�
// 2 1 ���ӽڵ�2->�ڵ�1��
// 2 3
// 1 4
// 2 4
// 4 5
// 3 5
// 3 4
// 2   ���ӽڵ�2���͹㲥��
// ��� 4
// ��Ŀ������֤���нڵ�ɴ�
// 
// �ҵ�˼·�Ƕ�ÿ���ڵ��ÿ��·�������м�¼�������ڽӾ���
// Ȼ�������дӷ��ͽڵ㿪ʼ��·��
// ÿ��·�����������Ľڵ㣬ʹ��һ��map��¼�������ڵ����С·��
// �����С·����2
// 
// ��Ȼ��ͼ���Ǻ���Ϥ��������˼·ҲӦ�ö�
// ����ͨ���ʺܵͣ���Ҫ���о���
// AC 10%
//

//
//3.3 ���Ϲ�ͨ
// �����������Լ�����һ��
// 400��
// 100 * 100% + 100 * 70% + 200 * 10% = 190
// 
// ���ۣ�
//	������������OK�� ˼·�淶����ȷ�Զ������Ե�
// 
// ����ֻҪ������ȫ��������������һ�����̰ɣ������и���λ�Ļ���
// 
//�����������ۺϲ���
// ���Ƶ����ʾ�
// �����������ʺ��������� ��һ�� ��ѹ�԰� �ֹ۶Ȱ�֮����
// 
//����
// Ҫ�˵��Ӱ������ͻȻ�뵽��û��
//

//
//3.4 ���繵ͨ
// �ۺϲ�������
// 
// ���ۣ�
// ûɶ���⣬ͦ�õ�
// 
//׼�����ż�������
// ���˻�����������⣬���Ƽ����滹���ʣ����о���
// ����ع�һ����Ŀ
// 
//ʱ�䣺
// ����һ����7��
// 
//����
// �ӽ�ͼ�����μӻ���������140�����һ��ƽ����20+
//

//
//3.7 ����1��
// welink�������� �����ߵ�
// ������������ָ�����һ�£�����ع�һЩ�ײ�֪ʶ
// 
//һ���㷨�⿪��
// �������0�ĸ���
// һ�����麬��0��1���ɰ�k��0�滻Ϊ1�����������0�ĸ���
int longestZeros(vector<int>& A, int k)
{
	//��������
	int left = 0, right = 0, ret = 0;
	int size = A.size();
	//��¼1�ĸ���
	int ones = 0;
	while (right < size) {
		//������һ��������У���1����滻������
		if (A[right] == 1)
			++ones;
		//���滻������ָ�����������̴���
		while (ones > k)
			if (A[left++] == 1)
				--ones;
		//�������ڼ�¼���ǰ���С�ڵ���k��1����
		ret = max(ret, right - left + 1);
		++right;
	}
	return ret;
}
// ˼·�����꿪ʼ����
// 
//��������
// ��Ŀ��أ��ѵ���
// 
// io���ã�select��poll��epoll����
// tcpЭ�顢��������
// domain socket
//  https://www.cnblogs.com/sparkdev/p/8359028.html
// �ڴ����ϣ��������Ż���ָ������
//  https://blog.csdn.net/GugeMichael/article/details/8207519
//  https://wingsxdu.com/posts/note/cpu-cache-and-memory-barriers/
//	֪��volatile����Ƿ�ֹ�������Ż��ģ���û�뵽��ָ��������ڴ������������ʻ����
// CASԭ�� 
//	http://www.zyiz.net/tech/detail-129644.html
//  http://www.pksure.com/backend/jdk/concurrent-cas
//	��������������
// Э�̺��̵߳�����
//  https://www.bilibili.com/read/cv9346691
// ��������������
//  https://www.jianshu.com/p/4b097aac2c9d
// ����
// �ڴ��û�����ҳ�ֶ�
// malloc���������ڴ��д��ռ�������ڴ�
// �Ĵ�������Щ
//  �Ĵ���%rdi, %rsi, %rdx, %rcx, %r8, %r9 �ֱ��������溯���� 6 ���������� %rax �������溯���ķ���ֵ��
// �������ĸ��Ĵ���
//  https://blog.csdn.net/qq_31917799/article/details/104233427
// linux�������� readelf objdump
//  https://blog.csdn.net/u014608280/article/details/81948141
// gcc����
//  https://wangchujiang.com/linux-command/c/gcc.html
// shell����
//  https://www.runoob.com/linux/linux-command-manual.html
// ������
// 
//���ٲ���û�д���������HR����
// 
//3.8 ����һ�淴��
// ͨ����������
// ����׼������ʱ�䰲�ż�������
// ��ʽ��һ����ͬ�����������ŵĽ�������
//

//
//3.10 ֪ͨ����7�㼼������
// 
//�ٹ�һ�����֪ʶ����������
// 
//���Լ�¼
// 
//

//
//��ΪOD�ṩ����ϰ���¼
//

//����ˮ��hard�� /problems/trapping-rain-water/
class Solution {
public:
	int trap(vector<int>& height) {
		//������������ÿ���ұ�������������ߵ�ǽ�ڣ���ô�����ˮ������������������һ��ǽ���Լ��ĸ߶�
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
		//DP��������������ߵ�ֵ�ȼ�¼������������ʱ��ֱ���ã�������ÿ�ζ�������һ��
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
		//˫ָ�룬��̬�滮�����������ʵֻ��һ�Σ���ʵ���Բ����������У��Ż��ռ�
		//Ȼ����������߷ֱ�ʼ���м��ң��ı߸�С���ͼ�����һ�ߣ���С��һ�ߵ���ֵ������Ч����Сֵ��
		if (height.empty() || height.size() < 3/* �����ǰ����β��ܴ�ˮ */) return 0;
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
		//ջ����������ƥ�䣬��ջ��¼�����εķ�Χ����˼·�Ƚ�����
		//��һ�¹ٷ��ⷨ
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

//�ַ���ѹ����easy�� https://leetcode-cn.com/problems/compress-string-lcci/
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
	//���Ҫ�����һ���ַ��Ĵ����ӽ�ȥ
	ret += to_string(count);
	return S.size() <= ret.size() ? S : ret;
}

//����˹�����ŷ⣨hard�� /problems/russian-doll-envelopes/
int maxEnvelopes(vector<vector<int>>& envelopes) {
	//��ͨdp O(logn+n^2)
	if (envelopes.empty() || envelopes[0].size() != 2) return 0;
	//�Ȱ�������򣬶ԱȺ���д��д����һ���Ľ��
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
			//ÿ���ŷ⿴�ܷ�װ����ǰ���ÿ���ŷ⣬װ����˵��Ҳװ���¸��ŷ�������ŷ�
			if (envelopes[i][0] > envelopes[j][0] && envelopes[i][1] > envelopes[j][1])
			{
				dp[i] = max(dp[i], dp[j] + 1);
				ret = max(ret, dp[i]);//ͬʱ��¼���ֵ��������һ�α���
			}
		}
	}
	return ret;
	//����Ϊ������������У���̰��˼����㣬����һ��ע�������
	sort(envelopes.begin(), envelopes.end(),
		[](const vector<int>& a, const vector<int>& b) {
			//������ͨ������������񣬼�Ȼ�ǵ������У���ô�����ܵ��ÿ�ߵĶ�ά��Ϊһά
			//Ҳ���ǿ����ʱ���ø߶ȸ��ߵ�����ǰ�棬�Ա�����̰�ĵ�˼�������ǰ�����������
			if (a[0] == b[0])
				return a[1] > b[1];
			return a[0] < b[0];
		});
	//���������м�¼��������С�ļ�¼Ԫ��
	vector<int> lis;
	for (auto& pair : envelopes)
	{
		//��Ԫ�������򣬱Ƚϸ�Ԫ��
		auto iter = lower_bound(lis.begin(), lis.end(), pair[1]);
		if (iter == lis.end())
			lis.push_back(pair[1]);
		else if (*iter > pair[1])
			*iter = pair[1];
	}
	return lis.size();
}

//�����ӳ�ʱ�䣨medium�� /problems/network-delay-time/
int networkDelayTime(vector<vector<int>>& times, int n, int k) {
	vector<pair<int, int>> adj[101];
	//������תΪ�ڽӱ�
	for (auto time : times)
		adj[time[0]].push_back({ time[2],time[1] });
	//�����������
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

//�������ʣ�medium�� /problems/word-search/
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

//�������medium�� /problems/largest-number
class largest_number {
public:
	struct string_cmp {
		bool operator()(const string& a, const string& b)
		{
			//�������������ĸ���ǰ����󣬻���������0ʱ��Ĭ�ϱȽϴ���
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
		//��ǰ������0ȥ�������ȫ0���
		while (ret[0] == '0' && ret.size() > 1)
			ret = ret.substr(1);
		return ret;
	}
};

//���������medium�� /problems/rectangle-area
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

//�����ַ�����Ƶ������medium�� /problems/sort-characters-by-frequency
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
	//�������д���������Լ�д�ȽϺ���
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

//������������medium�� /problems/basic-calculator-ii
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
			//�������ֺͿո�Ҳ���ǲ������ţ����ߵ���β�ˣ��ж���һ����������ʲô
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
				//����һ�κ����㣬��¼���β�����
				cur_num = 0;
				pre_op = s[i];
			}
		}
		//ʣ�µ�������Ӽ��ɣ������Ѿ�����ɸ��ţ�
		int ret = 0;
		for (auto num : cal)
			ret += num;
		return ret;
	}
};

//����������medium�� /problems/number-of-islands
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

//����֮�ͣ�medium�� /problems/3sum
class three_sum {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		vector<vector<int>> ret;
		int n = nums.size();
		sort(nums.begin(), nums.end());
		for (int index1 = 0; index1 + 2 < n/* ���滹�������������ճ��� */; ++index1)
		{
			if (index1 > 0 && nums[index1] == nums[index1 - 1])
				continue;//ȥ����߲���
			int index2 = index1 + 1, index3 = n - 1;
			while (index2 < index3)
			{
				int sum = nums[index1] + nums[index2] + nums[index3];
				if (sum == 0)
				{
					ret.push_back({ nums[index1],nums[index2],nums[index3] });
					//ȥ���ұ߲���
					--index3;
					while ((index2 < index3) && (nums[index3] == nums[index3 + 1])) --index3;
				}
				else if (sum < 0)//��̫С��˵����ߵ�̫С������
					++index2;
				else //��̫��˵���ұ�̫��ǰ��
					--index3;
			}
		}

		return ret;
	}
};

//�������У�hard�� /problems/permutation-sequence
class permutation_sequence {
public:
	string getPermutation(int n, int k) {
		//׼��1��n�����飨���ַ�����
		// ���� n = 4 , k = 15
		// 1��4������24�֣��Ե�һ������Ϊ��
		// 1��4ÿ�����ֿ�ͷ�ֱ���6�֣�Ҳ����(n-1)!��
		//ÿ�����ֵ�ѡ��
		// ��15�����֣�����ÿ�����ֿ�ͷ6�֣����2
		// Ҳ�����ַ���������Ϊ2������'3'
		// ȷ����һ������Ϊ3����������ʣ '124'
		// �ڶ�������ѡ����3��������ѡ���ܹ�6�֣�ÿ�����ֿ�ͷ�ֱ�2��
		// ֮ǰ15��6���ҵ���һ�����֣�ȡģ���3����ʣ��6������ȡ��3��
		// ��3�����֣�����ÿ������2�֣����1
		// Ҳ�����ַ���������Ϊ1������'2'����ǰ���� '32'
		// ȷ�ϵڶ������ֺ���������ʣ '14'
		// ������������2��������ѡ���ܹ�2�֣�ÿ�����ֿ�ͷ�ֱ�1��
		// 3��2ȡģ���1��Ҳ����ʣ������ȡ��1��
		// '321' ʣ�� '4'
		// ����ʣ��һ���ַ� '3214'
		//
		if (n == 1) return "1";
		//׼�������н׳���
		vector<int> fac(n + 1, 1);
		for (int i = 1; i <= n; ++i)
			fac[i] = i * fac[i - 1];
		//����뱸ѡ�ַ�
		string ret;
		vector<int> numbers;
		for (int i = 1; i <= n; ++i)
			numbers.push_back(i);
		//�ݹ�ѡ��ÿ������
		setPerm(numbers, ret, n, k, fac);
		return ret;
	}
	void setPerm(vector<int>& numbers, string& ret, int n, int k, vector<int>& fac)
	{
		if (n == 1)
		{
			//ֻʣ���һ���ˣ�ֱ�Ӽ�
			ret += to_string(numbers.back());
			return;
		}
		//ÿ���ַ���ͷ��(n-1)!�֣���k������ȥ��
		int index = k / fac[n - 1];
		//����պ���������Ӧ���ǵ�0��
		if (k % fac[n - 1] == 0)
			--index;
		//ƴ�ӵ�ǰ���ֲ��Ӻ�ѡ��ȥ��
		ret += to_string(numbers[index]);
		numbers.erase(numbers.begin() + index);
		//��һ��ѡ��ʱ�����Ǵ�n-1�����������ѡ�굱ǰ���ֺ�ĵ�k��
		k -= fac[n - 1] * index;
		//�ݹ�����߼�
		setPerm(numbers, ret, n - 1, k, fac);
	}
};

//�����ӣ�medium�� /problems/rotting-oranges/ 
class rott_orange {
public:
	int orangesRotting(vector<vector<int>>& grid) {
		//���ڿ��ܸտ�ʼ���ڶ�������ӣ�����Ӧ���Ǵ����������ӿ�ʼ�������������������dfs
		int m = grid.size();
		int n = grid[0].size();
		//bfsʹ�ö���
		queue<pair<int, int>> q;
		//���������׼����������ͳ������������
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
		//��ʼ����
		vector<int> dir = { -1,0,1,0,-1 };//�����ĸ�������ɢ�ĸ�������
		int ret = -1;//��һ��������ԭ�����ڵ������ӣ�+1����0��ʼ
		while (!q.empty())
		{
			int size = q.size();
			while (size-- > 0)
			{
				auto rott = q.front();
				q.pop();
				//���ĸ�������
				for (int i = 0; i < 4; ++i)
				{
					int x = rott.first + dir[i];
					int y = rott.second + dir[i + 1];
					//�ڷ�Χ����Ϊ�������Ӳż�����ɢ
					if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 1)
					{
						grid[x][y] = 2;
						q.push({ x,y });
						--fresh;//��¼��Ӱ�������
					}
				}
			}
			++ret;
		}
		//��������������ӣ�������Զ���ᱻӰ��
		if (fresh > 0) return -1;
		//û��û�����ӣ�����0
		if (ret == -1) return 0;
		return ret;
	}
};

//��С���Բeasy�� /problems/minimum-absolute-difference
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

//������У�medium�� /problems/count-and-say
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

//��������Ӽ���medium�� /problems/largest-divisible-subset
class largest_divisible_subset {
public:
	vector<int> largestDivisibleSubset(vector<int>& nums) {
		//������
		sort(nums.begin(), nums.end());
		int n = nums.size(), max_i = 0;
		vector<int> dp(n, 1);//��¼�Ե�i�����ֽ�β������Ӽ���С��Ĭ��Ϊ1����Ϊ�����Լ�������Ϊ�Ӽ�
		vector<int> pre(n, -1);//��¼�Ե�i�������β���Ӽ���ǰһ�������������Ա��ؽ�����Ӽ�
		vector<int> ret;
		//��ÿ������Ϊ��β��������Ͻ����������
		for (int i = 1; i < n; ++i)
		{
			for (int j = 0; j < i; ++j)
				if (nums[i] % nums[j] == 0 && dp[i] < dp[j] + 1)
					dp[i] = dp[j] + 1, pre[i] = j;
			if (dp[i] > dp[max_i]) max_i = i;
		}
		//����pre��¼��ǰ������Ū���Ӽ�
		while (max_i >= 0)
		{
			ret.push_back(nums[max_i]);
			max_i = pre[max_i];
		}
		return ret;
	}
};

//ʡ��������medium�� /problems/number-of-provinces
class provinces_number {
public:
	int findCircleNum(vector<vector<int>>& isConnected) {
		int n = isConnected.size();
		//��ά�ڽӾ����ʾ��ͼ���ԶԽ��߷ָ�������һ���ģ�����ֻ��һά��¼����
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

//�ϲ��������飨easy�� /problems/merge-sorted-array
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

//��N��̩����������easy�� /problems/n-th-tribonacci-number
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

//��ָoffer45 �������ų���С����medium�� 
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

//�������ϵ�������ʱ�̣�medium�� /problems/last-moment-before-all-ants-fall-out-of-a-plank
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

//ѹ���ַ�����medium�� /problems/string-compression
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

//�����ַ�����medium�� /problems/decode-string
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

//��������ؽ����У�medium�� /problems/queue-reconstruction-by-height
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

//�ж������У�easy�� /problems/is-subsequence
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

//������������hard�� /problems/basic-calculator
class calc {
public:
	int calculate(string s) {
		//�ݹ鷽ʽ
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
	//ջ��ʽ
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

//ѧ�����ڼ�¼��easy�� /problems/student-attendance-record-i
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

//�����������Σ�easy�� /problems/longer-contiguous-segments-of-ones-than-zeros
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

//ȫ���У�medium�� /problems/permutations
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

//��Ծ��Ϸ��medium�� /problems/jump-game-iii
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

//�ָ�����Ϊ�����Ӵ���medium�� /problems/split-array-into-consecutive-subsequences
class split_array_into_subseq {
public:
	//��ʹ����һ��̰���㷨��
	//	left ��һ�� hashmap��left[i] �����һ�û�з��õ� i ��������
	//	end ��һ�� hashmap��end[i] ���������� i ��β�����������е�����
	//	Ȼ���ҳ��Խ�����һһ��֡�
	//	����ҼȲ������������������е�ĩβ���һ�����֣�Ҳ����������ҵ������������֣��ҷ��� False
	//�ý�������Ĺؼ����ǣ���������� x-1 ��β����Ч�����У�
	// �򽫵�ǰ x ���������е�ĩβ���Ǳȴ����� x ��ͷ���������и���/���͵ķ��գ���Ϊ���ĳ�������Ϊ 3��
	//����Ϊ������������ʶ��ÿ�����ֿ����Ǹ�������������еĿ�ͷ���β��
	// ��������������һ��΢��֮����֤�����ӵ���ǰ���������Ǳȴ��������и��á�
	// �������� [1,2,3,4,5,5,6,7] �Լ�������ȴ��������ж����Ǹ��ӻᵼ�����⡣
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

//�������飨medium�� /problems/sort-an-array
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

//��������кͣ�easy�� /problems/maximum-subarray
class max_subarray {
public:
	int maxSubArray(vector<int>& nums) {
		//������
		int n = size(nums), ans = INT_MIN;
		for (int i = 0; i < n; i++)
			for (int j = i, curSum = 0; j < n; j++)
				curSum += nums[j],
				ans = max(ans, curSum);
		return ans;
		//dp
		//��¼��i��β������������
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

//��ӽ�������֮�ͣ�medium�� /problems/3sum-closest
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

//����������ĺͣ�medium) /problems/continuous-subarray-sum
class check_subarray_sum {
public:
	bool checkSubarraySum(vector<int>& nums, int k) {
		if (nums.size() < 2)
			return false;

		//ʹ��map��¼������i�ĺ͵�ģ
		unordered_map<int, int> umap;
		umap[0] = -1;
		int sum = 0;
		for (int i = 0; i < nums.size(); ++i)
		{
			sum += nums[i];
			sum %= k;
			//ÿ��ȡģ��֮����û��ģ��ͬ�ģ���˵��һ����������
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
		//��ʹ��map����ʹ��һ��pre���ӳټ�飬�Ա������г�������Ϊ2
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

//ֻ���������ļ��̣�medium�� /problems/2-keys-keyboard
class two_keys_board {
public:
	int minSteps(int n) {
		//��ѧ�ⷨ�������ֽ�
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
	//dp�ⷨ
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

//������й������ʱ�䣨hard�� /problems/find-minimum-time-to-finish-all-jobs
class min_time_finish_jobs {
public:
	//����һ��NP��ȫ�Ķ౳�����⡣��ˣ��ϸ�Լ��(k <= 12)��
	//	���ԣ�������Ҫ�������������������ǿ��Լӿ�һ�㣺
	//	���ٵ�ǰ����ѽ����ʹ���������޼���
	//	��������������˵Ĺ���ʱ����ͬ������ֻ��Ҫ��������һ����
	//	�����Ż��кܴ���������ǿ���ֻʹ��һ����ϣ�������ٹ���ʱ�䡣
	//	���¡���������������򣬵�������ɾ������Ϊû�����Ľ�������������ˡ�
	//	Ϊ�˸���Ч�ؼ�֦�����ǿ��Խ���ҵ���������򣬲�����һ��̰�Ľ������Ӧ����һ���ܺõĿ�ʼ��
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

//����������ͣ�hard�� /problems/consecutive-numbers-sum
class consecutive_num_sum {
public:
	int consecutiveNumbersSum(int N) {
		//˼��������������
		// ����һ������ N�����ǿ��԰���д�� 2 �����֡�3 �����֡�4 �����ֵȵ��ܺ͡������Ǽ������ϵ���еĵ�һ�������� x��
		// ��ˣ�����Ӧ����
		//	x + (x + 1) + (x + 2) + ... + k �� = N
		//	kx + k * (k - 1) / 2 = N ��ζ��
		//	kx = N - k * (k - 1) / 2
		//	��ˣ����ǿ��Լ���ÿ�� k ֵ�� RHS��������� k �ı�������ô���ǿ���ʹ�ô� x ��ʼ�� k ��� N ���ܺ͡�
		//	���ڣ���������ˣ�ֱ������Ӧ��ѭ����ȡ k ��ֵ�Ƕ��٣���ܼ򵥡����������£�RHS Ӧ�ô��� 0����
		//	N - k * (k - 1) / 2 > 0 ����ζ��
		//	k * (k - 1) < 2N ���Խ���Ϊ
		//	k * k < 2N ==> k < sqrt(2N)
		//	����㷨�����帴�Ӷ�Ϊ O(sqrt(N))
		//	PS��OJ �����𰸱ȿ��ܷ�ʽ�������� 1����Ϊ����Ϊ N ��дΪ N ����
		//  �������������Ϊ����Ҫ�������������ܺͣ�����ζ������ 2 �����֡�����Ϊ��ȡ��OJ������Ӧ�ô�1��ʼ����
		int count = 1;
		for (int k = 2; k < sqrt(2 * N); k++) {
			if ((N - (k * (k - 1) / 2)) % k == 0) count++;
		}
		return count;
	}
};

//���ʽ�����hard�� /problems/word-ladder
class word_ladder {
public:
	int ladderLength(string beginWord, string endWord, vector<string>& wordList) {

	}
};

//�ҳ�ż���а���Ԫ������Ӵ���medium�� /problems/find-the-longest-substring-containing-vowels-in-even-counts/
class longest_substring_contain_vowels {
public:

	//���ǲ���Ҫ֪��ȷ�еļ���������ֻ��Ҫһ��ָʾԪ����ż�����������ı�־����ˣ����ǿ���ʹ��λ�������ÿ��Ԫ����״̬������������Ӣ����ĸ����ֻ�� 5 ��Ԫ�������ǽ��� 32 �ֿ��ܵ���ϡ�
	//	���ڣ�������ǵ�����Ϊ�㣬��ô���ǵ��ַ���ֻ����ż��Ԫ�������⣬������� i �� j ��������ͬ�������ַ���[i + 1, j] ���������Ϊ�㡣��ˣ��Ӵ�[i + 1, j] Ҳֻ����żԪ����
	//	�㷨
	//	�����Ǳ������ǵ��ַ���ʱ�����Ǹ������룬������ÿ��������ϵ���С��������������Ժ����ַ�����������ͬ�����룬����ζ����С�����������͵�ǰ������������֮����ַ������������׼��
	//	���仰˵��������Ҫ�ҵ�ÿ��������ϵĵ�һ�������һ������֮��������롣
	//	��ע�⣬���������루����Ԫ���ļ�������ż��������һ�������� '-1' - �������Ǵ�һ��ʼ�Ͱ����ַ�����
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
	}
};

//�Ƴ�K�����֣�medium�� /problems/remove-k-digits
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

//K���Ʊ�ʾ��λ�ܺͣ�easy�� /problems/sum-of-digits-in-base-k
class sum_digits_in_base_k {
public:
	int sumBase(int n, int k) {
		int sum = 0;
		while (n != 0) sum += n % k, n = n / k;
		return sum;
	}
};

//��ǰ�����������й�����������medium�� /problems/construct-binary-tree-from-preorder-and-inorder-traversal/
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

//���Ƕ����ȣ�easy�� /problems/maximum-nesting-depth-of-the-parentheses
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

//������Σ�easy�� /problems/relative-ranks
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

//ʢˮ�����������medium�� /problems/container-with-most-water
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

//�����е�K�����Ԫ�أ�medium�� /problems/kth-largest-element-in-an-array
class kth_largest_element {
public:
	int findKthLargest(vector<int>& nums, int k) {
#if 0
		//��������k��
		sort(nums.begin(), nums.end());
		return nums[nums.size() - k];
#endif
		//��С��
		priority_queue<int, vector<int>, greater<int>> q;
		for (auto nums : nums)
		{
			q.push(nums);
			if (q.size() > k) q.pop();//ֻ��k��
		}
		return q.top();
	}
};

//����K��������ͣ�medium�� /problems/subarray-sum-equals-k
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

//�Խ��߱�����medium�� /problems/diagonal-traverse
class diagonal_traverse {
public:
	vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
		//�ֽ���������ֻ���ǵ�����Խ��ߣ��ٸ��з�ת
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
//��������������
// 
//��㲥��Ӧ
// ĳͨ����������N������ڵ㣬��1��N��ʶ�������нڵ��໥��ͨ���ڵ����Ϣ�����ӳ�Ϊһ��ʱ�䵥λ����Ȩ����ͼ��
// �ָ�������ڵ� link[i] = u,v ��u��v��ʾ����ڵ�
// ��ָ���ڵ㷢���㲥�����й㲥�ڵ��յ���Ϣ�󶼻���ԭ·�ظ���Ӧ������������Ҫ�����ȴ�ʱ������յ����нڵ���Ӧ
// ����ÿ���ڵ�����ʱ�� * 2��
// 
// ע��
// N ��Χ [1,1000]
// ����link���Ȳ�����3000���� 1 < u,v < N
// ����������ڵ�ɴ�
// 
// ���룺
// 5 7 ����һ�б�ʾ��5���ڵ㣬7��ڵ�������Ϣ��
// 2 1 ���ӽڵ�2->�ڵ�1��
// 2 3
// 1 4
// 2 4
// 4 5
// 3 5
// 3 4
// 2   ���ӽڵ�2���͹㲥��
// 
// �����
// 4 
//
class longest_broadcast_response
{
public:
	//�ڽӱ�
	vector<int> adj[1001];//N��Χ����������ӳٲ�ͬ����pair��¼Ȩ�أ�
	void run()
	{
		int N, I;//N���ڵ㣬I������
		while (cin >> N >> I)
		{
			int u, v;//��������
			for (int i = 0; i < I; ++i)
			{
				cin >> u >> v;
				adj[u].push_back(v);
			}
			int k;//�㲥�ڵ�
			cin >> k;

			vector<int> memo_dfs(N + 1, INT_MAX);//��¼��ÿ���ڵ�����ʱ��
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
	//���������������
	void dfs(vector<int>& memo, int node, int delay)
	{
		//�Ѿ��ȵ�ǰ��¼����ʱ�������û��Ҫ������ȥ��
		if (delay >= memo[node])
			return;
		//��¼���˽ڵ��ʱ��
		memo[node] = delay;
		//�ӵ�ǰ�ڵ��ܹ�����Ľڵ������������
		for (auto edge : adj[node])
			dfs(memo, edge, delay + 1);
	}
	//���������������
	void bfs(vector<int>& memo, int node)
	{
		//����һ������׼����ŵ�ǰ������ڵ�
		queue<int> q;
		q.push(node);
		//�ڵ�����ʱ��Ϊ0
		memo[node] = 0;
		//��ʼ�����
		while (!q.empty())
		{
			//ÿ���ڵ����ͬʱ������ڵ�������
			int cur = q.front();
			q.pop();
			for (auto edge : adj[cur])
			{
				//����ʱ������ľͲ��������
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