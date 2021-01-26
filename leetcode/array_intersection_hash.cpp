/**
*  如果使用哈希集合存储元素，则可以在 O(1) 的时间内判断一个元素是否在集合中，从而降低时间复杂度。
*/

#include <iostream>
#include <vector>
#include <unordered_set>  // 哈希集合

std::vector<int> get_intersection(std::unordered_set<int>& s1, std::unordered_set<int>& s2);

std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2)
{
	std::unordered_set<int> s1, s2;
	for (auto num : nums1) s1.insert(num);
	for (auto num : nums2) s2.insert(num);
	return get_intersection(s1, s2);
}

std::vector<int> get_intersection(std::unordered_set<int>& s1, std::unordered_set<int>& s2)
{
	if (s1.size() > s2.size()) return get_intersection(s2, s1);

	std::vector<int> result;
	for (auto num : s1)
	{
		if (s2.count(num))
		{
			result.push_back(num);
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