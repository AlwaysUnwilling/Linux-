/*************************************************************************
	> File Name: leetcode1.c
	> Author: 
	> Mail: 
	> Created Time: Thu 17 Feb 2022 10:55:38 PM CST
    > About:字符串中的第一个唯一字符:给定一个字符串 s ，找到 它的第一个不重复的字符，并返回它的索引 。如果不存在，则返回 -1 。
 ************************************************************************/

#include<iostream>
class Solution {
public:
    int firstUniqChar(string s) {
        int count[26]= {0};
          for(auto ch:s)
          {
              count[ch-'a']++;
          }
          for(size_t i=0;i<s.size();++i)
          {
              if(count[s[i]-'a']==1)
              return i;
          }
          return -1;
    }
};

