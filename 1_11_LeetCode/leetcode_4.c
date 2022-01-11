/*************************************************************************
	> File Name: leetcode_4.c
	> Author: 
	> Mail: 
	> Created Time: Tue 11 Jan 2022 10:11:32 PM CST
    >abort:轮转数组：给你一个数组，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。
 ************************************************************************/

#include<stdio.h>
//暴力解法
void rotate(int* nums, int numsSize, int k){
    k%=numsSize;
    while(k>0){
        int tmp=nums[numsSize-1];
        int end=numsSize-1;
        while(end>0){
            nums[end]=nums[end-1];
            end--;
        }
        nums[0]=tmp;
        k--;
    }
}

//新开数组
void rotate(int* nums, int numsSize, int k){
    if(nums==NULL){
        return;
    }
    k%=numsSize;
    int* tmp=(int*)malloc(sizeof(int)*numsSize);
    int j=0;
    for(int i=k;i>0;--i){
        tmp[j++]=nums[numsSize-i];
    }

    for(int i=0;i<numsSize-k;++i){
        tmp[j++]=nums[i];
    }  
    memcpy(nums,tmp,sizeof(int)*numsSize);
    free(tmp);
}
//旋转数组法

void reverse(int* nums,int left,int right)
{
    while(left<right){
        int tmp=nums[left];
        nums[left]=nums[right];
        nums[right]=tmp;
        left++;
        right--;
    }
}
void rotate(int* nums, int numsSize, int k){
    if(nums==NULL){
        return ;
    }
    k%=numsSize;
    reverse(nums,0,numsSize-k-1);
    reverse(nums,numsSize-k,numsSize-1);
    reverse(nums,0,numsSize-1);
}
//环状替换
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b, *b = t;
}

void rotate(int* nums, int numsSize, int k) {
    k = k % numsSize;
    int count = gcd(k, numsSize);
    for (int start = 0; start < count; ++start) {
        int current = start;
        int prev = nums[start];
        do {
            int next = (current + k) % numsSize;
            swap(&nums[next], &prev);
            current = next;
        } while (start != current);
    }
}

