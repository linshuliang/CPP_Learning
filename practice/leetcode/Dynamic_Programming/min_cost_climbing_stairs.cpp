// 746. 使用最小花费爬楼梯
#include <iostream>
#include <vector>
#include <algorithm>

// O(n) 空间复杂度
int minCostClimbingStairs(std::vector<int>& cost)
{
	int n = cost.size();
	std::vector<int> dp(n + 1, 0);
	dp[0] = dp[1] = 0;
	for (int i = 2; i <= n; i++)
	{
		dp[i] = std::min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
	}
	return dp[n];
}

// O(1) 空间复杂度
int minCostClimbingStairs_O1(std::vector<int>& cost)
{
	int n = cost.size();
	int prev_one = 0;	// 前面一个
	int prev_two = 0;	// 前面两个
	int ret;
	for (int i = 2; i <= n; i++)
	{
		ret = std::min(prev_one + cost[i - 1], prev_two + cost[i - 2]);
		prev_two = prev_one;
		prev_one = ret;
	}
	return ret;
}

void main()
{

}