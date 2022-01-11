/*************************************************************************
	> File Name: leetcode_3.c
	> Author: 
	> Mail: 
	> Created Time: Tue 11 Jan 2022 08:15:28 PM CST
    >About:合并俩个有序数组：给你两个按 非递减顺序 排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n ，分别表示 nums1 和 nums2 中的元素数目。

请你 合并 nums2 到 nums1 中，使合并后的数组同样按 非递减顺序 排列。

注意：最终，合并后数组不应由函数返回，而是存储在数组 nums1 中。为了应对这种情况，nums1 的初始长度为 m + n，其中前 m 个元素表示应合并的元素，后 n 个元素为 0 ，应忽略。nums2 的长度为 n 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/merge-sorted-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<stdio.h>
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n){
    int begin1=0,begin2=0;
    int* tmp=(int*)malloc(sizeof(int)*(m+n));
    if(tmp==NULL){
        exit(1);
    }
    int tmpi=0;
    while(begin1<m && begin2<n){
        if(nums1[begin1]<nums2[begin2]){
            tmp[tmpi++]=nums1[begin1++];
        }else{
            tmp[tmpi++]=nums2[begin2++];
        }
    }
    while(begin1<m){
        tmp[tmpi++]=nums1[begin1++];
    }
    while(begin2<n){
        tmp[tmpi++]=nums2[begin2++];
    }
    memcpy(nums1,tmp,sizeof(int)*(m+n));
    free(tmp);
}

