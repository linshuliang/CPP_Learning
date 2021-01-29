// 归并排序
#include <vector>
using namespace std;

class Solution {
public:
	vector<int> sortArray(vector<int>& nums) 
	{
		int left = 0;
		int right = nums.size() - 1;
		MergeSort(nums, left, right);
		return nums;
	}

	void MergeSort(vector<int>&nums, int left, int right)
	{
		if (left < right)//只要left<right，最终情况是left=right，即数组长度为1，单独一个数，肯定是有序的
		{
			int mid = (left + right) / 2;  //取中点
			MergeSort(nums, left, mid);  //左边块递归排序
			MergeSort(nums, mid + 1, right);
			Merge(nums, left, mid, mid + 1, right);  //左右块合并
		}
	}

	void Merge(vector<int>&nums, int L1, int R1, int L2, int R2)//L1,R1是第一块的左右索引，L2R2同理，将两个块合并
	{
		int* temp = new int(R2 - L1 + 1); //存放合并后的有序数组（这里没用vector，用了会提示内存不足）
		int i = L1;
		int j = L2;
		int k = 0;
		while (i <= R1 && j <= R2) 
		{
			if (nums[i] < nums[j])
			{
				temp[k++] = nums[i++];
			}
			else
			{
				temp[k++] = nums[j++];
			}
		}  //while结束之后若有某块没遍历完（另一块肯定已经遍历完），剩下的数直接赋值
		while (i <= R1) temp[k++] = nums[i++];
		while (j <= R2) temp[k++] = nums[j++];
		for (int i = 0; i < k; i++)  //合并后的数赋值回原来的数组
			nums[L1 + i] = temp[i];

		delete temp;
	}
};