#include<iostream>
#include<vector>

using namespace std;

//62. 不同路径
/*
 *一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。

问总共有多少条不同的路径？
 * */

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m,vector<int>(n));
        for(int i=0;i < m;++i){
            dp[i][0]=1;
        }
        for(int j=0;j < n;++j){
            dp[0][j]=1;
        }
        for(int i=1;i < m;++i){
            for(int j=1;j < n;++j){
                dp[i][j]=dp[i-1][j]+dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};

//55. 跳跃游戏
/*
 *给定一个非负整数数组 nums ，你最初位于数组的 第一个下标 。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标。
 * */
class Solution {
public:
    bool canJump(vector<int>& nums) {
        if(nums.size()==1){
            return true;
        }
        int n=nums.size();
        int maxReach=0;
        for(int i=0;i <= maxReach && maxReach < n-1;++i){
            maxReach=max(i+nums[i],maxReach);
        }
        return maxReach>=n-1;
    }
};
