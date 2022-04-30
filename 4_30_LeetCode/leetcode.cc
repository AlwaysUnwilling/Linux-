#include<iostream>
#include<stdlib.h>
#include<vector>
#include<limits.h>


//213. 打家劫舍 II
/*
 *你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都 围成一圈 ，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警 。

给定一个代表每个房屋存放金额的非负整数数组，计算你 在不触动警报装置的情况下 ，今晚能够偷窃到的最高金额。
 * */

//动态规划:分别取(start,end)==(0,nums.size()-2)和(1,nums.size()-1)计算

class Solution {
public:
    int getWealth(std::vector<int> nums,int begin,int end)
    {
        nums[begin+1]=std::max(nums[begin],nums[begin+1]);
        int index=begin+2;
        while(index<=end){
            nums[index]=std::max(nums[index-1],nums[index-2]+nums[index]);
            index++;
        }
        return nums[end];
    }
    int rob(std::vector<int>& nums) {
        if(nums.size()==1) return nums[0];
        if(nums.size()==2) return std::max(nums[0],nums[1]);
        return std::max(getWealth(nums,0,nums.size()-2),getWealth(nums,1,nums.size()-1));
    }
};

//908. 最小差值 I
/*
 *给你一个整数数组 nums，和一个整数 k 。

在一个操作中，您可以选择 0 <= i < nums.length 的任何索引 i 。将 nums[i] 改为 nums[i] + x ，其中 x 是一个范围为 [-k, k] 的整数。对于每个索引 i ，最多 只能 应用 一次 此操作。

nums 的 分数 是 nums 中最大和最小元素的差值。 

在对  nums 中的每个索引最多应用一次上述操作后，返回 nums 的最低 分数 。
 * */

/*
 *思路与算法:整数数组的最大值maxNums和最小值minNums；如果maxNums-minNums<=2*K;那么通过操作我们可以将他们
 全都改为同一个数字，因此最低分数为0；如果maxNums-minNums>2*K,最低分数为maxNums-minNums-2*k；
 * */

class Solution1 {
public:
    int smallestRangeI(std::vector<int>& nums, int k) {
        if(nums.size()==1) return 0;
        int maxNums=INT_MIN;
        int minNums=INT_MAX;
        for(auto& e:nums){
            if(e>maxNums){
                maxNums=e;
            }
            if(e<minNums){
                minNums=e;
            }
        }
        return maxNums-minNums>=2*k?maxNums-minNums-2*k:0;
    }
};
