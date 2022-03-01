#pragma once

#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <unordered_set>
using namespace std;

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
	
}