/*************************************************************************
	> File Name: leetcode_2.c
	> Author: 
	> Mail: 
	> Created Time: Tue 11 Jan 2022 07:22:06 PM CST
    >About:删除有序数组中的重复项：给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。

不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<stdio.h>
//双指针
int removeDuplicates(int* nums, int numsSize){
    if(numsSize==1 || numsSize==0){
        return numsSize;
    }
    int prev=0;
    int cur=prev+1;

    while(cur<numsSize){
        if(nums[prev]!=nums[cur]){
            ++prev;
            nums[prev]=nums[cur];
        }
        ++cur;
    }
    return prev+1;
}

