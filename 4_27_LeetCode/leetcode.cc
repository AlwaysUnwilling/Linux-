#include<iostream>


using namespace std;

//868. 二进制间距
/*
 *给定一个正整数 n，找到并返回 n 的二进制表示中两个 相邻 1 之间的 最长距离 。如果不存在两个相邻的 1，返回 0 。

如果只有 0 将两个 1 分隔开（可能不存在 0 ），则认为这两个 1 彼此 相邻 。两个 1 之间的距离是它们的二进制表示中位置的绝对差。例如，"1001" 中的两个 1 的距离为 3 。
 * */

class Solution {
public:
    int binaryGap(int n) {
        if(n==0) return 0;
        int max=0;
        while(n){
            if(n&1){
                int tmp=n;
                int dis=0;
                while(tmp){
                    if((tmp>>1)&1){
                        break;
                    }
                    dis++;
                    tmp>>=1;
                }
                if(tmp && dis+1>max){
                    max=dis+1;
                }
            }
            n>>=1;
        }
        return max;
    }
};

//398. 随机数索引
/*
 *给你一个可能含有 重复元素 的整数数组 nums ，请你随机输出给定的目标数字 target 的索引。你可以假设给定的数字一定存在于数组中。

实现 Solution 类：

Solution(int[] nums) 用数组 nums 初始化对象。
int pick(int target) 从 nums 中选出一个满足 nums[i] == target 的随机索引 i 。如果存在多个有效的索引，则每个索引的返回概率应当相等。
 * */

//方法一：哈希表

class Solution {
public:
    Solution(vector<int>& nums) {
        for(int i=0;i<nums.size();++i){
            indexmap[nums[i]].push_back(i);
        }
    }
    
    int pick(int target) {
        vector<int>& index=indexmap[target];
        return index[rand()%index.size()];
    }
    private:
    unordered_map<int,vector<int>> indexmap;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */


