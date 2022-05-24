#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

//462. 最少移动次数使数组元素相等 II
/*
 *给你一个长度为 n 的整数数组 nums ，返回使所有数组元素相等需要的最少移动数。

在一步操作中，你可以使数组中的一个元素加 1 或者减 1 。
 * */

class Solution {
public:
    int minMoves2(vector<int>& nums) {
        if(nums.size()==0 || nums.size()==1){
            return 0;
        }
        sort(nums.begin(),nums.end());
        int mid=nums[(nums.size()-1)/2];
        int count=0;
        for(auto& e:nums){
            count+=abs(abs(e-mid));
        }
        return count;
    }
};


