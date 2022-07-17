#include<iostream>
#include<vector>

using namespace std;

//39. 组合总和
/*
 *给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，找出 candidates 中可以使数字和为目标数 target 的 所有 不同组合 ，并以列表形式返回。你可以按 任意顺序 返回这些组合。

candidates 中的 同一个 数字可以 无限制重复被选取 。如果至少一个数字的被选数量不同，则两种组合是不同的。 

对于给定的输入，保证和为 target 的不同组合数少于 150 个。
 * */

class Solution {
public:
    void dfs(vector<int>& candidates,vector<vector<int>>& vv,vector<int>& v,int target,int index)
    {
        if(index==candidates.size()){
            return;
        }
        if(target==0){
            vv.push_back(v);
            return ;
        }
        dfs(candidates,vv,v,target,index+1);
        if(target-candidates[index]>=0){
            v.push_back(candidates[index]);
            dfs(candidates,vv,v,target-candidates[index],index);
            v.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> vv;
        vector<int> v;
        dfs(candidates,vv,v,target,0);
        return vv;
    }
};

//46. 全排列
/*
 *给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。
 * */

class Solution {
public:
    void dfs(vector<int>& nums,vector<vector<int>>& vv,vector<int>& v,vector<bool>& visited,int index,int n)
    {
        if(index >= n){
            vv.push_back(v);
            return;
        }
        for(int i = 0;i < n;++i){
            if(!visited[i]){
                visited[i]=true;
                v.push_back(nums[i]);
                dfs(nums,vv,v,visited,index+1);
                v.pop_back();
                visited[i]=false;
            }
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> vv;
        vector<int> v;
        vector<bool> visited(nums.size(),false);
        int n=nums.size();
        for(int i=0;i < n;++i){
            v.push_back(nums[i]);
            visited[i]=true;
            dfs(nums,vv,v,visited,1,n);
            v.pop_back();
            visited[i]=false;
        }
        return vv;
    }
};
