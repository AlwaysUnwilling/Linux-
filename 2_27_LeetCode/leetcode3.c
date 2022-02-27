/*************************************************************************
	> File Name: leetcode3.c
	> Author: 
	> Mail: 
	> Created Time: Sun 27 Feb 2022 11:37:02 PM CST
    > About: 两个数组的交集 II:给你两个整数数组 nums1 和 nums2 ，请你以数组形式返回两数组的交集。返回结果中每个元素出现的次数，应与元素在两个数组中都出现的次数一致（如果出现次数不一致，则考虑取较小值）。可以不考虑输出结果的顺序。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/intersection-of-two-arrays-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<stdio.h>
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        map<int,int> m1;
        for(auto e: nums1){
            m1[e]++;
        }
        map<int,int> m2;
        for(auto e:nums2){
            m2[e]++;
        }
        vector<int> v;
        for(auto e:m1){
            auto it=m2.find(e.first);
            if(it!=m2.end()){
                int minSize=e.second;
                if(it->second<e.second){
                    minSize=it->second;
                }
                while(minSize--){
                    v.push_back(e.first);
                }
            }
        }
        return v;
    }
};
