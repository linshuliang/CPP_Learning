// leetcode 70  -- 爬梯子
#include <iostream>
#include <vector>

// 空间复杂度为 O(n)
int climbStairs(int n)
{
	if (n < 1)
		return 0;
	else if (n == 1)
		return 1;
	else if (n == 2)
		return 2;

	std::vector<int> dp(n + 1, 0);
	dp[1] = 1;
	dp[2] = 2;

	for (int i = 3; i <= n; i++)
	{
		dp[i] = dp[i - 1] + dp[i - 2];
	}

	return dp[n];
}

// 空间复杂度为 O(1)
int climbStairs_O1(int n)
{
	if (n < 1)
		return 0;
	else if (n == 1)
		return 1;
	else if (n == 2)
		return 2;

	int p = 1;
	int q = 2;
	int r;

	for (int i = 3; i <= n; i++)
	{
		r = p + q;
		p = q;
		q = r;
	}

	return r;
}

void main()
{
	for (int i = 1; i < 30; i++)
	{
		std::cout << i << "  " << climbStairs(i) << std::endl;
	}
}