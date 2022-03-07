/*************************************************************************
	> File Name: newcode.c
	> Author: 
	> Mail: 
    > Created Time: Mon 07 Mar 2022 11:09:23 PM CST
    > About:在一个二维数组中（每一个一维数组的长度都相同），没一行都按照从左到右递增的顺序排序，每一列都按照从上到下
      递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数
 ************************************************************************/

#include<iostream>

class Solution
{
public:
    bool Find(int target,vector<vector<int>> array){
        int i=0,j=array[0].size()-1;
        while(i<array.size() && j>=0){
            if(target<array[i][j]){
                j--;
            }else if(target>array[i][j]){
                i++;
            }else{
                return true;
            }
        }
        return false;
    }
};
