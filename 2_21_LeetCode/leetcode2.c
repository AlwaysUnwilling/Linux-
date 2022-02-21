/*************************************************************************
	> File Name: leetcode2.c
	> Author: 
	> Mail: 
	> Created Time: Mon 21 Feb 2022 11:24:25 PM CST
    > About:删除有序数组中的重复项:给你一个 升序排列 的数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。元素的 相对顺序 应该保持 一致 。

由于在某些语言中不能改变数组的长度，所以必须将结果放在数组nums的第一部分。更规范地说，如果在删除重复项之后有 k 个元素，那么 nums 的前 k 个元素应该保存最终结果。

将最终结果插入 nums 的前 k 个位置后返回 k 。

不要使用额外的空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<iostream>
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size()==0 || nums.size()==1){
            return nums.size();
        }
        int cur=0,next=1;
        int size=1;
        while(next<nums.size()){
            while(next<nums.size() && nums[cur]==nums[next]){
                next++;
            }
            if(next>=nums.size()){
                break;
            }
            nums[++cur]=nums[next];
            ++size;
            ++next;
        }
        return size;
    }
};
