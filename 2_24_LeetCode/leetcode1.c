/*************************************************************************
	> File Name: leetcode1.c
	> Author: 
	> Mail: 
	> Created Time: Thu 24 Feb 2022 11:22:58 PM CST
    > About: 连续子数组的最大和:描述
输入一个长度为n的整型数组array，数组中的一个或连续多个整数组成一个子数组，子数组最小长度为1。求所有子数组的和的最大值。
数据范围:
1 <= n <= 2\times10^51<=n<=2×10 
5
 
-100 <= a[i] <= 100−100<=a[i]<=100

要求:时间复杂度为 O(n)O(n)，空间复杂度为 O(n)O(n)
进阶:时间复杂度为 O(n)O(n)，空间复杂度为 O(1)O(1)
 ************************************************************************/

#include<iostream>
#include<vector>
class Solution {
public:
    int FindGreatestSumOfSubArray(vector<int> array) {
        int tmp=0,max_ret=0;
        for(auto e:array){
            if(tmp+e<0){
                tmp=0;
            }else{
                tmp+=e;
            }
            max_ret=max(max_ret,tmp);
        }
        if(max_ret!=0){
            return max_ret;
        }
        return *max_element(array.begin(),array.end());
    }
};
