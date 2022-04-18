#include<iostream>
#include<vector>

using namespace std;

//386. 字典序排数
/*
 *给你一个整数 n ，按字典序返回范围 [1, n] 内所有整数。

你必须设计一个时间复杂度为 O(n) 且使用 O(1) 额外空间的算法。
 * */

class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> ret(n);
        int number = 1;
        //如果number*10<=n;那么number*10就是下一个字典序数字
        //如果number%10==9 || number+1>n 那么说明最低位数字已经完成排序，取出末尾数字number/=10;
        //直到number%10!=9 && number+1<=n,那么number++就是下一个字典序的数字
        for (int i = 0; i < n; i++) {
            ret[i] = number;
            if (number * 10 <= n) {
                number *= 10;
            } else {
                while (number % 10 == 9 || number + 1 > n) {
                    number /= 10;
                }
                number++;
            }
        }
        return ret;
    }
};

//198. 打家劫舍
/*
 *你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额
 * */

class Solution {
public:
    int rob(vector<int>& nums) {
        /*动态规划:F(i)---表示小偷偷窃第i个房屋时的最大收益；
        //转移方程F(i)=max(F(i-2)+nums[i],F(i-1));即因为不能偷连续的俩家，因此最大的收益一定是他偷
        //i-2个房屋时的最大收益+当前房屋的收益和小偷偷前i-1个房屋时的最大收益(当前房屋不能偷)中的最大值
        //初始值：F(1):第一家的最大收益即：nums[0];F(2):前俩家的最大收益：max(nums[0],nums[1]);*/
        if(nums.size()==1){
            return nums[0];
        }
        if(nums.size()==2){
            return max(nums[0],nums[1]);
        }
        nums[1]=max(nums[0],nums[1]);
        for(int i=2;i<nums.size();++i){
            nums[i]=max(nums[i-2]+nums[i],nums[i-1]);
        }
        return nums[nums.size()-1];
    }
};

//121. 买卖股票的最佳时机
/**
 * 给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。

你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。

返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。
 * /
 
 ////记录第i天之前(包含第i天)的最低股价；更新当天的卖出的最大利润(maxProfit=max(maxProfit,e-minPrice));
 class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size()<2){
            return 0;
        }
        int minPrice=INT_MAX,maxProfit=0;
        for(auto e:prices){
            if(e<minPrice){
                minPrice=e;
            }
            maxProfit=max(maxProfit,e-minPrice);
        }
        return maxProfit;
    }
};
