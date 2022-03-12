/*************************************************************************
	> File Name: newcode.c
	> Author: 
	> Mail: 
	> Created Time: Sat 12 Mar 2022 10:18:13 PM CST
    > About:动态规划--斐波那契数列，现在要求输入一个整数n，请输出斐波那契数列的第n（从0
    开始，第0项为0，第一项为1）
 ************************************************************************/

#include<iostream>
//递归算法
class Solution
{
public:
    int Fibonacci(int n){
        if(n==0){
            return 0;
        }
        if(n==1){
            return 1;
        }
        return Fibonacci(n-1)+Fibonacci(n-2);
    }
};
class Solution1
{
public:
    int Fibonacci(int n){
        if(n==0){
            return 0;
        }
        if(n==1){
            return 1;
        }
        //初始化初值
        int F0=0,F1=1;
        int ret=0;
        for(int i=2;i<=n;++i)
        {
            //转移方程
            ret=F0+F1;
            F0=F1;
            F1=ret;
        }
        return ret;
    }
};
