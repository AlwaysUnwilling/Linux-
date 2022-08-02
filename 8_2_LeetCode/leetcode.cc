#include<iostream>
#include<vector>
#include<unordered_set>

using namespace std;

//128. 最长连续序列
/*
 *给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

请你设计并实现时间复杂度为 O(n) 的算法解决此问题。
 * */

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n=nums.size();
        if(n<=1){
            return n;
        }
        unordered_set<int> st;
        for(const auto& num:nums){
            st.insert(num);
        }   
        int ret=0; 
        for(const auto& num:st){
            if(!st.count(num-1)){  //如果num-1在st中存在，则跳过
                int length=1;
                int i=1;     //查找从num开始的连续的数字是否在st中存在
                while(st.count(num+i)){
                    length++;
                    i++;
                }
                ret=max(length,ret);
            }
        }
        return ret;
    }
};

//279. 完全平方数
/*
 *给你一个整数 n ，返回 和为 n 的完全平方数的最少数量 。

完全平方数 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。
 * */

////动态规划：组成和为n的完全平方数的数一定在[1,sqrt(n)]的范围内，
//在该区间遍历，假如i是一个在该区域的一个值,即：1<=i*i<=sqrt(n);
//那么接下来就是查找组成n-i*i的完全平方数的最小数量；所有的结果中的最小数量即为所求
class Solution {
public:
    int numSquares(int n) {
        if(n==1){
            return 1;
        }
        vector<int> v(n+1);
        for(int i=1;i<=n;++i){
            int cnt=INT_MAX;
            for(int j=1;j*j<=i;++j){
                cnt=min(cnt,v[i-j*j]);
            }
            v[i]=1+cnt;
        }
        return v[n];
    }
};
