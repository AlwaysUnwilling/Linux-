#include<iostream>
#include<vector>

using namespace std;

//442. 数组中重复的数据
/*
 *给你一个长度为 n 的整数数组 nums ，其中 nums 的所有整数都在范围 [1, n] 内，且每个整数出现 一次 或 两次 。请你找出所有出现 两次 的整数，并以数组形式返回。

你必须设计并实现一个时间复杂度为 O(n) 且仅使用常量额外空间的算法解决此问题。
 * */


/*
 * 方法一：将元素交换到对应的位置:我们对数组进行一次遍历。当遍历到位置i时，我们知道nums[i] 应该被放在位置nums[i]−1。因此我们交换num[i] 和 nums[nums[i]−1] 即可，直到待交换的两个元素相等为止。
 * */
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            while (nums[i] != nums[nums[i] - 1]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (nums[i] - 1 != i) {
                ans.push_back(nums[i]);
            }
        }
        return ans;
    }
};

//方法二：使用正负号作为标记
/*
 * 遍历数组，判断nums[nums[i]-1]的正负性：如果为正表示该数字第一次出现，将nums[nums[i]-1]变负；
 * 否则表示该数字第二次出现，即为答案
 * */

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            int x = abs(nums[i]);
            if (nums[x - 1] > 0) {
                nums[x - 1] = -nums[x - 1];
            }
            else {
                ans.push_back(x);
            }
        }
        return ans;
    }
};

