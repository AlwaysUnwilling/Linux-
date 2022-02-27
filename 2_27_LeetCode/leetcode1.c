/*************************************************************************
	> File Name: leetcode1.c
	> Author: 
	> Mail: 
	> Created Time: Sun 27 Feb 2022 11:12:59 PM CST
    > About:在长度 2N 的数组中找出重复 N 次的元素:给你一个整数数组 nums ，该数组具有以下属性：

nums.length == 2 * n.
nums 包含 n + 1 个 不同的 元素
nums 中恰有一个元素重复 n 次
找出并返回重复了 n 次的那个元素。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/n-repeated-element-in-size-2n-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<stdio.h>
class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        unordered_map<int,int> um;
        for(auto e:nums){
            um[e]++;
        }
        for(auto e:um){
            if((e.second)*2==nums.size()){
                return e.first;
            }
        }
        return -1;
    }
};
