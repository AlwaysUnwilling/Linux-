/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Wed 23 Feb 2022 09:57:05 PM CST
    > About:只出现一次的数字 III:给定一个整数数组 nums，其中恰好有两个元素只出现一次，其余所有元素均出现两次。 找出只出现一次的那两个元素。你可以按 任意顺序 返回答案。

 

进阶：你的算法应该具有线性时间复杂度。你能否仅使用常数空间复杂度来实现？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/single-number-iii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<iostream>
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        vector<int> v;
        if(nums.size()==0 || nums.size()==1){
            return v;
        }
        int tmp=0;
        for(auto e:nums){
            tmp^=e;
        }
        size_t i=0;
        for(;i<32;++i){
            if(tmp&(1<<i)){
                break;
            }
        }
        int ans1=0,ans2=0;
        for(auto e:nums){
            if(e&(1<<i)){
                ans1^=e;
            }else{
                ans2^=e;
            }
        }
        v.push_back(ans1);
        v.push_back(ans2);
        return v;
    }
};
