#include <vector>
#include <iostream>
#include <algorithm>

class Solution
{
public:
	int search(std::vector<int>& nums, int target)
	{
		std::sort(nums.begin(), nums.end(), std::less<int>());
		return binary_search(nums, target);
	}

	int binary_search(std::vector<int>& nums, int target)
	{
		int left = 0;
		int right = nums.size() - 1;
		while (left <= right)
		{
			int pivot = left + (right - left + 1) / 2;
			if (target == nums[pivot])
				return pivot;
			else if (target < nums[pivot])
				right = pivot - 1;
			else
				left = pivot + 1;
		}
		return -1;
	}
};

void main()
{
	std::vector<int> nums = { 1, 9, 6, 3, 2, 5, 9, 4, 11 };
	Solution s;
	int target = 13;
	auto ret = s.search(nums, target);
	if (ret == -1)
		std::cout << target << " is not in array" << std::endl;
	else
		std::cout << target << " found in array, index = " << ret << std::endl;

	system("pause");
}