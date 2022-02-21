/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Mon 21 Feb 2022 10:47:34 PM CST
    > About:只出现一次的数字:给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。

说明：

你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/single-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<iostream>
#include<vector>
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ret=0;
        for(auto e:nums){
            ret^=e;
        }
        return ret;
    }
};
