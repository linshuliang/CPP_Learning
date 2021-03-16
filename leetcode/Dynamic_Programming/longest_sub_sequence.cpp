/* 
* leetcode 300
* 给你一个整数数组 nums, 找到其中最长严格递增子序列的长度。
* 子序列是由数组派生而来的序列，删除（或不删除）数组中的元素，不改变其余元素的顺序。
* 例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。
*/
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

int lengthOfLIS(const vector<int>& nums)
{
	int n = nums.size();
	if (n == 0) return 0;

	std::vector<int> dp(n, 1);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (nums[j] < nums[i])
				dp[i] = std::max(dp[i], dp[j] + 1);
		}
	}

	return *std::max_element(dp.begin(), dp.end());
}

int main()
{
	std::vector<int> nums = { 10, 9, 2,5, 3, 7, 101, 18 };
	int ret = lengthOfLIS(nums);
	std::cout << ret << std::endl;

	return 0;
}