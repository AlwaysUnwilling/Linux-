#include<iostream>
#include<vector>
#include<stack>

using namespace std;

//739. 每日温度
/*
 *给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。
 * */

//暴力解法
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        if(temperatures.size()==0 || temperatures.size()==1){
            return {};
        }
        int step=1;
        int n=temperatures.size();
        vector<int> ret(n);
        for(int i=0;i < n;++i){
            bool isFind=false;
            for(int j=i+1;j < n;++j){
                if(temperatures[i] < temperatures[j]){
                    ret[i]=step;
                    step=1;
                    isFind=true;
                    break;
                }else{
                    step++;
                }
            }
            if(!isFind){
                step=1;
            }
        }
        return ret;
    }
};

//单调栈
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        if(temperatures.size()==0 || temperatures.size()==1){
            return {};
        }
        int n=temperatures.size();
        stack<pair<int,int>> sp;
        vector<int> ret(n,0);
        for(int i=n-1;i>=0;--i){
            if(sp.empty()){
                sp.push({temperatures[i],i});
            }else if(sp.top().first > temperatures[i]){
                sp.push({temperatures[i],i});
                ret[i]=1;
            }else{
                while(!sp.empty() && sp.top().first <= temperatures[i]){
                    sp.pop();
                }
                if(!sp.empty()){
                    ret[i]=sp.top().second-i;
                }
                sp.push({temperatures[i],i});
            }
        }
        return ret;
    }
};

#include<algorithm>

//31. 下一个排列
/*
 *整数数组的一个 排列  就是将其所有成员以序列或线性顺序排列。

例如，arr = [1,2,3] ，以下这些都可以视作 arr 的排列：[1,2,3]、[1,3,2]、[3,1,2]、[2,3,1] 。
整数数组的 下一个排列 是指其整数的下一个字典序更大的排列。更正式地，如果数组的所有排列根据其字典顺序从小到大排列在一个容器中，那么数组的 下一个排列 就是在这个有序容器中排在它后面的那个排列。如果不存在下一个更大的排列，那么这个数组必须重排为字典序最小的排列（即，其元素按升序排列）。

例如，arr = [1,2,3] 的下一个排列是 [1,3,2] 。
类似地，arr = [2,3,1] 的下一个排列是 [3,1,2] 。
而 arr = [3,2,1] 的下一个排列是 [1,2,3] ，因为 [3,2,1] 不存在一个字典序更大的排列。
给你一个整数数组 nums ，找出 nums 的下一个排列。

必须 原地 修改，只允许使用额外常数空间。
 * */

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if(nums.size()==1){
            return;
        }
        int n=nums.size();
        int lindex=-1;
        for(int i=n-1;i>0;--i){
            if(nums[i] > nums[i-1]){
                lindex=i-1;
                break;
            }
        }
        if(lindex==-1){
            reverse(nums.begin(),nums.end());
            return;
        }
        for(int i=n-1;i>=lindex+1;--i){
            if(nums[i] > nums[lindex]){
                swap(nums[i],nums[lindex]);
                sort(nums.begin()+lindex+1,nums.end());
                break;
            }
        }
    }
};
