#include<iostream>
#include<map>
#include<vector>


using namespace std;

//剑指 Offer 03. 数组中重复的数字
//在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。

class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        map<int,int> m;
        int ret=0;
        for(auto e:nums){
            if(m[e]>0){
                ret=e;
                break;
            }else{
                m[e]++;
            }
        }
        return ret;
    }
};

//剑指 Offer 53 - I. 在排序数组中查找数字 I
//统计一个数字在排序数组中出现的次数。
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if(nums.size()==0){
            return 0;
        }
        if(nums.size()==1){
            return nums[0]==target? 1:0;
        }
        int left=0;
        int right=nums.size()-1;
        int count=0;
        while(left<=right){
            int midIndex=(left+right)>>1;
            if(nums[midIndex]==target){
                int tmpIndex=midIndex;
                while(tmpIndex>=0 && nums[tmpIndex--]==target){
                    count++;
                }
                tmpIndex=midIndex+1;
                while(tmpIndex<nums.size() && nums[tmpIndex++]==target){
                    count++;
                }
                return count;
            }else if(nums[midIndex]>target){
                right=midIndex-1;
            }else{
                left=midIndex+1;
            }
        }
        return count;
    }
};

//剑指 Offer 53 - II. 0～n-1中缺失的数字
//一个长度为n-1的递增排序数组中的所有数字都是唯一的，并且每个数字都在范围0～n-1之内。在范围0～n-1内的n个数字中有且只有一个数字不在该数组中，请找出这个数字

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int left=0;
        int right=nums.size()-1;
        while(left<=right){
            int midIndex=(left+right)>>1;
            if(nums[midIndex]==midIndex){
                left=midIndex+1;
            }else{
                right=midIndex-1;
            }
        }
        return left;
    }
};
