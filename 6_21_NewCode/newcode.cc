#include<iostream>
#include<vector>
#include<cmath>
#include<limits.h>

using namespace std;

//DP7 连续子数组的最大乘积
/*
 *描述
输入一个长度为 n 的整型数组 nums，数组中的一个或连续多个整数组成一个子数组。求所有子数组的乘积的最大值。
1.子数组是连续的，且最小长度为 1 ，最大长度为 n
2.长度为 1 的子数组，乘积视为其本身，比如 [4] 的乘积为 4
3.该题的数据保证最大的乘积不会超过 int 的范围，即不超过2^{32}-12 
32
 −1
数据范围:
1 <= n <= 2\times10^51<=n<=2×10 
5
 
-100 <= a[i] <= 100−100<=a[i]<=100
输入描述：
第一行输入一个正整数 n ，表示数组的长度
第二行输入 n 个整数，表示数组中的值。
输出描述：
输出子数组的乘积的最大值
 * */

int main()
{
    int n;
    while(cin>>n){
        vector<int> v(n);
        for(int i=0;i<n;++i){
            cin>>v[i];
        }
        int imax=1;//数组前i个数字中乘积最大的值
        int imin=1;//数组前i个数字中成绩最小的值
        int ans=INT_MIN;
        for(int i=0;i<n;++i){
            if(v[i]<0){
                swap(imax,imin);//(i-1)max*v[i]当v[i]<0时会变成最小值，反之imin会变成最大值
            }
            imax=max(imax*v[i],v[i]);
            imin=min(imin*v[i],v[i]);
            ans=max(ans,imax);
        }
        cout<<ans<<endl;
    }
    return 0;
}

//DP5 有多少个不同的二叉搜索树
/*
 *描述
给定一个由节点值从 1 到 n 的 n 个节点。请问由多少种不同的方法用这 n 个节点构成互不相同的二叉搜索树。

数据范围： 1 \le n \le 19 \1≤n≤19 
输入描述：
仅一行输入一个正整数 n ，表示节点的数量。
输出描述：
输出组成不同二叉搜索树的方法数。
 * */

//动态规划：取有序数列中某节点i做为根节点，此时把搜索二叉树分为1~i-1和i+1~n俩部分，二叉搜索树的个数f(i,n)=
//dp[i-1]*dp[n-i]不同的二叉搜索树的总和，即(1<=i<=n)作为根节点的总和；即可得：dp[n]+=dp[i-1]*dp[n-i];

int main()
{
    int n;
    while(cin>>n){
        if(n<2){
            cout<<n<<endl;
            continue;
        }
        vector<int> dp(n+1);
        dp[0]=1; //0个节点的搜索二叉树个数为1
        dp[1]=1; //1个节点的搜索二叉树个数为1
        for(int i=2;i<=n;++i){
            for(int j=1;j<=i;++j){
                dp[i]+=dp[j-1]*dp[i-j];
            }
        }
        cout<<dp[n]<<endl;
    }
    return 0;
}
