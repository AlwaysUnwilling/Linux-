/*************************************************************************
	> File Name: leetcode1.c
	> Author: 
	> Mail: 
	> Created Time: Wed 23 Feb 2022 10:31:55 PM CST
    > About:只出现一次的数字 II:给你一个整数数组 nums ，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次 。请你找出并返回那个只出现了一次的元素。
 ************************************************************************/

#include<iostream>
#include<vector>
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        vector<int> v;
        int ret=0;
        v.resize(32,0);
        for(auto e:nums){
            for(size_t i=0;i<32;++i){
                if(e&(1<<i)){
                    v[i]++;
                }
            }
        }
        for(size_t i=0;i<32;++i){
            if(v[i]%3==1){
                ret|=(1<<i);
            }
        }
        return ret;
    }
};
