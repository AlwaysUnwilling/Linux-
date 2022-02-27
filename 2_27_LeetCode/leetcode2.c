/*************************************************************************
	> File Name: leetcode2.c
	> Author: 
	> Mail: 
	> Created Time: Sun 27 Feb 2022 11:20:23 PM CST
    > About:两个数组的交集:给定两个数组 nums1 和 nums2 ，返回 它们的交集 。输出结果中的每个元素一定是 唯一 的。我们可以 不考虑输出结果的顺序 。
 ************************************************************************/

#include<stdio.h>
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> s1;
        for(auto e:nums1){
            s1.insert(e);
        }
        unordered_set<int> s2;
        for(auto e:nums2){
            s2.insert(e);
        }
        vector<int> v;
        for(auto e:s1){
            if(s2.find(e)!=s2.end()){
                v.push_back(e);
            }
        }
        return v;
    }
};
