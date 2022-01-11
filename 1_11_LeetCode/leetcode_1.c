/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Tue 11 Jan 2022 07:09:49 PM CST
    >About:移除元素：给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。

不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。

元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/remove-element
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<stdio.h>
//暴力解法
int removeElement(int* nums, int numsSize, int val){
    int i=0;
    while(i<numsSize) {
        if(nums[i]==val){
            int end=i;
            while(end+1<numsSize){
                nums[end]=nums[end+1];
                ++end;
            }
            --numsSize;
        }else{
            ++i;
        }
    }
    return numsSize;
}

//双指针法
int removeElement(int* nums, int numsSize, int val){
    int cur=0,prev=0;
    while(cur<numsSize){
        if(nums[cur]==val){
            ++cur;
        }else{
            nums[prev++]=nums[cur++];
        }
    }
    return prev;
}

