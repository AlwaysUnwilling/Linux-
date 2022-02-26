/*************************************************************************
	> File Name: leetcode1.c
	> Author: 
	> Mail: 
	> Created Time: Sat 26 Feb 2022 08:56:02 PM CST
    > About: 数组中的第K个最大元素:给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。

请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素
 ************************************************************************/

#include<iostream>
#include<vector>
#include<priority_queue>

//solution 1
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        return nums[nums.size()-k];
    }
};
//solution 2
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int,vector<int>,less<int>> pq;
        for(auto e:nums){
            pq.push(e);
        }
        while(--k){
            pq.pop();
        }
        return pq.top();
    }
};

