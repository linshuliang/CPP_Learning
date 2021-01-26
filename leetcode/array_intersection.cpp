#include <iostream>
#include <algorithm>
#include <vector>

std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2)
{
	std::sort(nums1.begin(), nums1.end());
	std::sort(nums2.begin(), nums2.end());

	int length1 = nums1.size();
	int length2 = nums2.size();

	int index1 = 0;
	int index2 = 0;

	std::vector<int> result;
	while (index1 < length1 && index2 < length2)
	{
		
		if (nums1[index1] == nums2[index2])
		{
			if (result.empty() || nums1[index1] != result.back()) result.push_back(nums1[index1]);
			index1++;
			index2++;
		}
		else if (nums1[index1] < nums2[index2])
		{
			index1++;
		}
		else
		{
			index2++;
		}
	}
	return result;
}

void main()
{
	std::vector<int> nums1 = { 1, 2, 3, 5, 6, 8, 11, 13, 20 };
	std::vector<int> nums2 = { 7, 9, 11, 19, 20 };

	std::vector<int> same_elements = intersection(nums1, nums2);
	for (auto it = same_elements.begin(); it != same_elements.end(); it++)
		std::cout << *it << "  ";
	std::cout << std::endl;
}