#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

/*
 *最接近的三数之和
 给你一个长度为 n 的整数数组 nums 和 一个目标值 target。请你从 nums 中选出三个整数，使它们的和与 target 最接近。

返回这三个数的和。

假定每组输入只存在恰好一个解。
 * */

using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(),nums.end());
        int ans=0;
        int gap=INT_MAX;
        for(int i=0;i < nums.size()-2;++i)
        {
            int left=i+1;
            int right=nums.size()-1;
            while(left < right)
            {
                if(nums[i]+nums[left]+nums[right] > target)
                {
                    if(gap > abs(target-nums[i]-nums[left]-nums[right]))
                    {
                        gap=abs(target-nums[i]-nums[left]-nums[right]);
                        ans=nums[i]+nums[left]+nums[right];
                    }
                    right--;
                }
                else if(nums[i]+nums[left]+nums[right] == target)
                {
                    ans=target;
                    return ans;
                }
                else 
                {
                    if(gap > abs(target-nums[i]-nums[left]-nums[right]))
                    {
                        gap=abs(target-nums[i]-nums[left]-nums[right]);
                        ans=nums[i]+nums[left]+nums[right];
                    }
                    left++;
                }
            }
        }
        return ans;
    }
};

/*
 * 找出字符串中第一个匹配项的下标
 *  给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串的第一个匹配项的下标（下标从 0 开始）。如果 needle 不是 haystack 的一部分，则返回  -1 。
 * */

class Solution {
public:
    int strStr(string haystack, string needle) {
        if(haystack.size()==0 || needle.size()==0)
        {
            return -1;
        }
        if(haystack.size() < needle.size())
        {
            return -1;
        }
        int index=0;
        bool flag=false;
        while(index < haystack.size() && (haystack.size()-index >= needle.size()))
        {
            string str=haystack.substr(index,needle.size());
            if(str==needle)
            {
                flag=true;
                break;
            }
            index++;
        }
        return flag==true?index:-1;
    }
};
