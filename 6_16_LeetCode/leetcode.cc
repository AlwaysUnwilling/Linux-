#include<iostream>
#include<set>
#include<algorithm>

using namespace std;

//532. 数组中的 k-diff 数对
/*
 *给定一个整数数组和一个整数 k，你需要在数组里找到 不同的 k-diff 数对，并返回不同的 k-diff 数对 的数目。

这里将 k-diff 数对定义为一个整数对 (nums[i], nums[j])，并满足下述全部条件：

0 <= i < j < nums.length
|nums[i] - nums[j]| == k
注意，|val| 表示 val 的绝对值。
 * */

//排序+暴力求解
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        if(nums.size()==0 || nums.size()==1){
            return 0;
        }
        sort(nums.begin(),nums.end());
        set<pair<int,int>> st;
        int n=nums.size();
        for(int i=0;i<n;++i){
            for(int j=n-1;j>i;--j){
                if(k==abs(nums[j]-nums[i])){
                    st.insert({nums[i],nums[j]});
                }
            }
        }
        return st.size();
    }
};

//排序+双指针
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        if(nums.size()==0 || nums.size()==1){
            return 0;
        }
        sort(nums.begin(),nums.end());
        int n=nums.size();
        int right=0;
        int count=0;
        for(int left=0;left<n;++left){
            //去重
            if(left==0 || nums[left]!=nums[left-1]){
                while(right<n && (nums[right]<nums[left]+k || right<=left)){
                    right++;
                }
                if(right<n && nums[right]==k+nums[left]){
                    count++;
                }
            }
        }
        return count;
    }
};

//哈希表

#include<unordered_set>

class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        unordered_set<int> visited;
        unordered_set<int> ret;
        for(auto& e:nums){
            if(visited.count(e-k)){
                //如果e-k已经被访问过
                ret.insert(e-k);
            }
            if(visited.count(k+e)){
                ret.insert(e);
            }
            visited.insert(e);
        }
        return ret.size();
    }
};

