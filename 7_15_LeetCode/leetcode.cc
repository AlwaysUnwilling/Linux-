#include<iostream>
#include<vector>

using namespace std;

//33. 搜索旋转排序数组
/*
 *整数数组 nums 按升序排列，数组中的值 互不相同 。

在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。

给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。

你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。
 * */

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int right=nums.size()-1;
        int left=0;
        while(left<=right){
            int mid=(left+right)>>1;
            if(nums[mid]==target){
                return mid;
            }else {
                if(nums[left]<nums[mid]){
                    //[left,mid)是有序的
                    int beg=left;
                    int end=mid-1;
                    while(beg<=end){
                        int index=(beg+end)>>1;
                        if(nums[index]==target){
                            return index;
                        }else if(nums[index]>target){
                            end=index-1;
                        }else{
                            beg=index+1;
                        }
                    }
                    left=mid+1;
                }else{
                    //(mid,right]是有序的
                    int beg=mid+1;
                    int end=right;
                    while(beg<=end){
                        int index=(beg+end)>>1;
                        if(nums[index]==target){
                            return index;
                        }else if(nums[index]>target){
                            end=index-1;
                        }else{
                            beg=index+1;
                        }
                    }
                    right=mid-1;
                }
            }
        }
        return -1;
    }
};

//34. 在排序数组中查找元素的第一个和最后一个位置
/*
 *给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。请你找出给定目标值在数组中的开始位置和结束位置。

如果数组中不存在目标值 target，返回 [-1, -1]。

你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。
 * */

class Solution {
public:
    int searchIndex(vector<int>& nums,int target,bool FLAG)
    {
        int left=0,right=(int)nums.size()-1;
        int ret=(int)nums.size();
        while(left<=right){
            int mid=(left+right)/2;
            if(nums[mid] > target || (FLAG && nums[mid]>=target)){
                right=mid-1;
                ret=mid;
            }else{
                left=mid+1;
            }
        }
        return ret;
    }
    vector<int> searchRange(vector<int>& nums, int target) {

        //求得target在nums中最左边的下标:找到与target相等的值得最左下标
        int leftIndex=searchIndex(nums,target,true);
        //求得target在nums中最右边的下标:找到大于target的第一个值得下标-1即使所求
        int rightIndex=searchIndex(nums,target,false)-1;
        //判断左右下标是否合法
        if (leftIndex <= rightIndex && rightIndex < nums.size() 
            && nums[leftIndex] == target && nums[rightIndex] == target) {
            return vector<int>{leftIndex, rightIndex};
        } 
        return vector<int>{-1, -1};
    }
};
