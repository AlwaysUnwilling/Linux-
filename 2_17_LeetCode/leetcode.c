/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Thu 17 Feb 2022 10:39:53 PM CST
    > About: 仅仅反转字母:给定一个字符串 S，返回 “反转后的” 字符串，其中不是字母的字符都保留在原地，而所有字母的位置发生反转。
 ************************************************************************/

#include<iostream>
class Solution {
public:
    bool IsALetter(char ch)
    {
        if((ch>='a' && ch<='z') || (ch>='A' && ch<='Z')){
            return true;
        }else{
            return false;
        }
    }
    string reverseOnlyLetters(string s) {
        if(s.size()==0){
            return s;
        }
        int begin=0;
        int end=s.size()-1;
        while(begin<end){
            if(IsALetter(s[begin]) && IsALetter(s[end])){
                swap(s[begin],s[end]);
                ++begin;
                --end;
            }else if(IsALetter(s[begin])==false){
                ++begin;
            }else if(IsALetter(s[end])==false){
                --end;
            }
        }
        return s;
    }
};

