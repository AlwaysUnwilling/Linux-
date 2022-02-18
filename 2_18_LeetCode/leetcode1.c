/*************************************************************************
	> File Name: leetcode1.c
	> Author: 
	> Mail: 
	> Created Time: Fri 18 Feb 2022 11:19:05 PM CST
    > About: 验证回文串:给定一个字符串，验证它是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。

说明：本题中，我们将空字符串定义为有效的回文串。
 ************************************************************************/

#include<iostream>
#include<string>
class Solution {
public:
    bool IsNumOrLetter(char& ch)
    {
        if(ch>='0' && ch<='9')
        return true;
        else if(ch<='z' && ch >= 'a')
        {
            ch-=32;
            return true;
        }
        else if(ch<='Z' && ch>='A')
        return true;
        else
        return false;
    }
    bool isPalindrome(string s) {
        int left = 0 ,right = s.size()-1;
        while(left<right)
        {
            while(left<right && IsNumOrLetter(s[left])==false)
            ++left;
            while(left<right && IsNumOrLetter(s[right])==false)
            --right;
            if(left>=right){
                break;
            }
            if(s[left] != s[right])
            return false;
            else
            {
                ++left;
                --right;
            }
        }
        return true;
    }
};
