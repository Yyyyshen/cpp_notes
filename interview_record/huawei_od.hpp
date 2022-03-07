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
// �ڴ����ϣ��������Ż���ָ������
// CASԭ��
// Э�̺��̵߳�����
// ����
// �ڴ��û�
// malloc�����д��ռ�������ڴ�
// �Ĵ�������Щ
// �������ĸ��Ĵ���
// linux�������� readelf objdump
// gcc����
// shell����
// ������
// 
//���ٲ���û�д���������HR����
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