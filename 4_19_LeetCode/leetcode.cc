#include<iostream>
#include<string>
#include<unordered_set>
#include<vector>
#include<cmath>

using namespace std;

//821. 字符的最短距离
/*
 *给你一个字符串 s 和一个字符 c ，且 c 是 s 中出现过的字符。

返回一个整数数组 answer ，其中 answer.length == s.length 且 answer[i] 是 s 中从下标 i 到离它 最近 的字符 c 的 距离 。

两个下标 i 和 j 之间的 距离 为 abs(i - j) ，其中 abs 是绝对值函数。
 * */
class Solution {
public:
    vector<int> shortestToChar(string s, char c) {
        vector<int> v;
        if(s.length()==0) return v;
        v.resize(s.length(),0);
        unordered_set<int> us;
        for(int i=0;i<s.length();++i){
            if(s[i]==c){
                us.insert(i);
            }
        }
        for(int i=0;i<s.length();++i){
            int minlen=INT_MAX;
            for(auto e:us){
                //cout<<"us: "<<e<<endl;
                if(abs(e-i)<minlen){
                    minlen=abs(e-i);
                }
            }
            v[i]=minlen;
        }
        return v;
    }
};


