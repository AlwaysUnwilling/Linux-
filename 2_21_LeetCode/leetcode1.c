/*************************************************************************
	> File Name: leetcode1.c
	> Author: 
	> Mail: 
	> Created Time: Mon 21 Feb 2022 11:11:13 PM CST
    > About:杨辉三角:给定一个非负整数 numRows，生成「杨辉三角」的前 numRows 行。

在「杨辉三角」中，每个数是它左上方和右上方的数的和。



 
 ************************************************************************/

#include<iostream>
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> vv;
        vector<int> v;
        if(numRows==0){
            return vv;
        }
        vv.resize(numRows);
        for(size_t i=0;i<numRows;++i){
            vv[i].resize(i+1);
            for(size_t j=0;j<=i;++j){
                if(j==0 || i==j){
                    vv[i][j]=1;
                }else{
                    vv[i][j]=vv[i-1][j]+vv[i-1][j-1];
                }
            }
            std::cout<<std::endl;
        }
        return vv;
    }
};
