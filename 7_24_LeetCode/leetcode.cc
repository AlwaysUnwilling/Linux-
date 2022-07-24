#include<iostream>
#include<vector>

using namespace std;

//78. 子集
/*
 *给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。

解集 不能 包含重复的子集。你可以按 任意顺序 返回解集
 * */

class Solution {
public:
    void _subsets(vector<int>& nums,vector<vector<int>>& vv,vector<int>& v,int index)
    {
        if(index>=nums.size()){
            vv.push_back(v);
            return;
        }
        v.push_back(nums[index]);
        _subsets(nums,vv,v,index+1);
        v.pop_back();
        _subsets(nums,vv,v,index+1);
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        if(nums.size()==1){
            return {{},{nums[0]}};
        }
        vector<vector<int>> vv;
        vector<bool> visited(nums.size(),false);
        vector<int> v;
        _subsets(nums,vv,v,0);
        return vv;
    }
};
