#include<iostream>
#include<vector>

using namespace std;

//DP8 乘积为正数的最长连续子数组
/*
 *描述
给定一个长度为 n 的整数数组，请你找出其中最长的乘积为正数的子数组长度。
子数组的定义是原数组中一定长度的连续数字组成的数组。

数据范围： 1 \le n \le 10^5 \1≤n≤10 
5
   , 数组中的元素满足 |val| \le 10^9 \∣val∣≤10 
9
  
输入描述：
第一行输入一个正整数 n ，表示数组长度。
第二行输入 n 个整数，表示数组中的元素。
输出描述：
输出最长的乘积为正数的子数组长度
 * */

//动态规划
int main()
{
    int n;
    while (cin >> n) {
        vector<int> v(n);
        for (int i = 0; i < n; ++i) {
            cin >> v[i];
        }
        int flag = 1;
        vector<int> dp(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            if (v[i] == 0) {
                dp[i + 1] = 0;
                flag = 1;
            }
            else if (v[i] < 0) {
                if (flag == 1) {
                    dp[i + 1] = -1 * (dp[i] + 1);
                    flag = dp[i+1];
                }
                else {
                    dp[i + 1] = dp[i] < 0 ? abs(flag) + 1 : abs(flag) + dp[i] + 1;
                    flag = 1;
                }
            }
            else {
                dp[i + 1] = dp[i] > 0 ? dp[i] + 1 : 1;
            }
        }
        int maxLeng = 0;
        for (const auto& e : dp) {
            if (e > maxLeng) {
                maxLeng = e;
            }
        }
        cout << maxLeng << endl;
    }
    return 0;
}


