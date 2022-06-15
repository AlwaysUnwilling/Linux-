#include<iostream>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>

using namespace std;

//719. 找出第 K 小的数对距离
/*
 *数对 (a,b) 由整数 a 和 b 组成，其数对距离定义为 a 和 b 的绝对差值。

给你一个整数数组 nums 和一个整数 k ，数对由 nums[i] 和 nums[j] 组成且满足 0 <= i < j < nums.length 。返回 所有数对距离中 第 k 小的数对距离。
 * */

//暴力求解
class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        int n=nums.size();
        //priority_queue<int,vector<int>,greater<int>> pq;
        map<int,int> m;
        for(int i=0;i<n;++i){
            for(int j=n-1;j>i;--j){
                //pq.push(abs(nums[i]-nums[j]));
                m[abs(nums[i]-nums[j])]++;
            }
        }
        int res=0;
        /*while(k--){
            res=pq.top();
            pq.pop();
        }*/
        int tmp=0;
        for(auto& e:m){
            tmp+=e.second;
            if(k<=tmp){
                res=e.first;
                break;
            }
        }
        return res;
    }
};

//排序+二分查找
class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        int n=nums.size();
        int left=0;
        int right=nums.back()-nums.front();
        while(left<=right){
            int mid=(left+right)>>1;
            int count=0;
            for(int j=0;j<n;++j){
                int i=lower_bound(nums.begin(),nums.begin()+j,nums[j]-mid)-nums.begin();
                count+=j-i;
            }
            if(count>=k){
                right=mid-1;
            }else{
                left=mid+1;
            }
        }
        return left;
    }
};

//排序 + 二分查找 + 双指针

class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        int n=nums.size();
        int left=0;
        int right=nums.back()-nums.front();
        while(left<=right){
            int mid=(left+right)>>1;
            int count=0;
            for (int i = 0, j = 0; j < n; j++) {
                while (nums[j] - nums[i] > mid) {
                    i++;
                }
                count += j - i;
            }
            if(count>=k){
                right=mid-1;
            }else{
                left=mid+1;
            }
        }
        return left;
    }
};
