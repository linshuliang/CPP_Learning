#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
	std::vector<int> sortArray(std::vector<int>& nums)
	{
		quickSort(nums, 0, nums.size() - 1);
		return nums;
	}

	void quickSort(std::vector<int>& nums, int left, int right)
	{
		if (left < right)
		{
			int mid = partition(nums, left, right);
			quickSort(nums, left, mid - 1);
			quickSort(nums, mid + 1, right);
		}
	}

	int partition(std::vector<int>& nums, int left, int right)
	{
		int pivot = nums[right];  // 选取最右边的元素作为 pivot
		int i = left;  // 分割位置
		for (int j = left; j < right; j++)
		{
			if (nums[j] < pivot)
			{
				std::swap(nums[i], nums[j]);
				i++;
			}
		}
		nums[right] = nums[i];
		nums[i] = pivot;
		return i;
	}
};

void main()
{
	std::vector<int> nums = { 1, 6, 3, 2, 5, 9, 4, 11 };
	Solution s;
	nums = s.sortArray(nums);
	for (auto it = nums.begin(); it != nums.end(); it++) std::cout << *it << std::endl;
	system("pause");
}
