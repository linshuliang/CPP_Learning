#include <iostream>
#include <algorithm>
#include <vector>

class Solution
{
public:
	std::vector<int> sortArray(std::vector<int>& nums)
	{
		quick_sort(nums, 0, nums.size() - 1);
		return nums;
	}

	void quick_sort(std::vector<int>& nums, int left, int right)
	{
		if (left < right)
		{
			int mid = partition(nums, left, right);
			quick_sort(nums, left, mid - 1);
			quick_sort(nums, mid + 1, right);
		}
	}

	int partition(std::vector<int>& nums, int left, int right)
	{
		int pivot = nums[left];
		int i = left + 1;
		int j = right;

		while (true)
		{
			while (i <= j && nums[i] <= pivot) i++;
			while (i <= j && nums[j] >= pivot) j--;
			if (i > j) break;
			std::swap(nums[i], nums[j]);
		}

		std::swap(nums[j], nums[left]);
		return j;
	}
};

void main()
{
	std::vector<int> nums = { 1, 9, 6, 3, 2, 5, 9, 4, 11 };
	Solution s;
	nums = s.sortArray(nums);
	for (auto it = nums.begin(); it != nums.end(); it++) std::cout << *it << std::endl;
	system("pause");
}
