/*************************************************************************
	> File Name: leetcode1.c
	> Author: 
	> Mail: 
	> Created Time: Sat 19 Feb 2022 11:37:07 PM CST
    > About:反转字符串中的单词 III:给定一个字符串 s ，你需要反转字符串中每个单词的字符顺序，同时仍保留空格和单词的初始顺序。
 ************************************************************************/

#include<iostream>
class Solution {
public:
    void Reverse(string& str,int begin,int end)
    {
        while(begin<end){
            swap(str[begin],str[end]);
            ++begin;
            --end;
        }
    }
    string reverseWords(string s) {
        if(s.size()==0 || s.size()==1){
            return s;
        }
        int num=s.size();
        int left=0;
        int right=0;
        while(right<s.size()){
            if(s[right]==' '){
                Reverse(s,left,right-1);
                ++right;
                left=right;
            }else{
                ++right;
            }
        }
        if(left==s.size()){
            return s;
        }
        Reverse(s,left,right-1);
        return s;
    }
};
