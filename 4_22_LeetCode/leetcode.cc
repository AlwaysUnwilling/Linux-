#include<iostream>
#include<vector>
#include<limits.h>

using namespace std;

//396. 旋转函数
/*
 *给定一个长度为 n 的整数数组 nums 。

假设 arrk 是数组 nums 顺时针旋转 k 个位置后的数组，我们定义 nums 的 旋转函数  F 为：

F(k) = 0 * arrk[0] + 1 * arrk[1] + ... + (n - 1) * arrk[n - 1]
返回 F(0), F(1), ..., F(n-1)中的最大值 。

生成的测试用例让答案符合 32 位 整数。
 * */

/*
 * 思路
记数组nums的元素之和为 numSum。根据公式，可以得到：
F(0) = 0*nums[0] + 1*nums[1] + ... + (n-1)*nums[n-1];
F(1) = 1*nums[0] + 2*nums[1] + ... + 0*nums[n-1] = F(0) +numSum - n*nums[n-1];
更一般地，当 1≤k<n 时，F(k) = F(k-1) +numSum - n*nums[n-k]我们可以不停迭代计算出不同的 F(k)，并求出最大值。
 * */
class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        if(nums.size()==1){
            return 0;
        }
        int max=INT_MIN;
        int n=nums.size();
        int f0=0;
        int f1=0;
        int sum=0;
        for(int i=0;i<n;++i){
            f0+=nums[i]*i;
            sum+=nums[i];
        }
        for(int i=1;i<n;++i){
            f1=f0+sum-n*nums[n-i];
            max=(f1>f0?f1:f0)>max?(f1>f0?f1:f0):max;
            f0=f1;
        }
        return max;
    }
};
