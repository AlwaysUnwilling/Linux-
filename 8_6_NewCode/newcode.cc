#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;

//BM83 字符串变形
/*
 *描述
对于一个长度为 n 字符串，我们需要对它做一些变形。

首先这个字符串中包含着一些空格，就像"Hello World"一样，然后我们要做的是把这个字符串中由空格隔开的单词反序，同时反转每个字符的大小写。

比如"Hello World"变形后就变成了"wORLD hELLO"。

数据范围: 1\le n \le 10^61≤n≤10 
6
  , 字符串中包括大写英文字母、小写英文字母、空格。
进阶：空间复杂度 O(n)O(n) ， 时间复杂度 O(n)O(n)
 * */

class Solution {
public:
    bool isSpace(char ch)
    {
        return ch==' ';
    }
    string trans(string s, int n) {
        // write code here
        string ret;
        int i=n-1;
        while(i>=0){
            string word;
            if(!isSpace(s[i])){
                while(i>=0 && !isSpace(s[i])){
                    if(s[i]>='a' && s[i]<='z'){
                        s[i]-=32;
                    }else{
                        s[i]+=32;
                    }
                    word+=s[i--];
                } 
                reverse(word.begin(),word.end());
                ret+=word;
            }else{
               ret+=' '; 
                i--;
            }
        }
        return ret;
    }
};

//BM97 旋转数组
/*
 *描述
一个数组A中存有 n 个整数，在不允许使用另外数组的前提下，将每个整数循环向右移 M（ M >=0）个位置，即将A中的数据由（A0 A1 ……AN-1 ）变换为（AN-M …… AN-1 A0 A1 ……AN-M-1 ）（最后 M 个数循环移至最前面的 M 个位置）。如果需要考虑程序移动数据的次数尽量少，要如何设计移动的方法？

数据范围：0 < n \le 1000<n≤100，0 \le m \le 10000≤m≤1000
进阶：空间复杂度 O(1)O(1)，时间复杂度 O(n)O(n)
 * */

class Solution {
public:
    /**
     * 旋转数组
     * @param n int整型 数组长度
     * @param m int整型 右移距离
     * @param a int整型vector 给定数组
     * @return int整型vector
     */
    vector<int> solve(int n, int m, vector<int>& a) {
        // write code here
        if(n==1){
            return a;
        }
        int cnt=m%n;
        reverse(a.begin(),a.end());
        reverse(a.begin(),a.begin()+cnt);
        reverse(a.begin()+cnt,a.end());
        return a;
    }
};

//BM84 最长公共前缀
/*
 *描述
给你一个大小为 n 的字符串数组 strs ，其中包含n个字符串 , 编写一个函数来查找字符串数组中的最长公共前缀，返回这个公共前缀。

数据范围： 0 \le n \le 50000≤n≤5000， 0 \le len(strs_i) \le 50000≤len(strs[ i])≤5000
进阶：空间复杂度 O(n)O(n)，时间复杂度 O(n)O(n)
 * */

class Solution {
public:
    /**
     * 
     * @param strs string字符串vector 
     * @return string字符串
     */
    string longestCommonPrefix(vector<string>& strs) {
        // write code here
        if(strs.size()==0){
            return "";
        }
        int minLen=INT_MAX;
        for(const string& str:strs){
            if(str.size() < minLen){
                minLen=str.size();
            }
        }
        string ret;
        for(int i=0;i < minLen;++i){
            char tmp=strs[0][i];
            int j=0;
            for(;j < strs.size();++j){
                if(strs[j][i]!=tmp){
                    break;
                }
            }
            if(j==strs.size()){
                ret+=tmp;
            }
        }
        return ret;
    }
};
