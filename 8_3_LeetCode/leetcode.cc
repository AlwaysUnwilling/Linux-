#include<iostream>
#include<string>
#include<vector>


using namespace std;

//139. 单词拆分
/*
 * 给你一个字符串 s 和一个字符串列表 wordDict 作为字典。请你判断是否可以利用字典中出现的单词拼接出 s 。

注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。
 * */

//暴力递归求解
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        if(s.size()==0){
            return true;
        }

        for(const auto& str:wordDict){
            size_t pos=s.find(str);
            if(pos!=string::npos){
                string tmp1=s.substr(0,pos);
                string tmp2=s.substr(pos+str.size());
                if(wordBreak(tmp1,wordDict) && wordBreak(tmp2,wordDict)){
                    return true;
                }
            }
        }
        return false;
    }
};

//动态规划
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> us;
        for(const auto& str:wordDict){
            us.insert(str);
        }
        size_t n=s.size();
        vector<bool> v(n+1,false); //v[i]表示s的前i个(0-i)的字串可以在wordDict中完全找到 
        v[0]=true;//""字符串可以在wordDict中找到
        for(int i=1;i < n+1;++i){
            for(int j=0;j < i;++j){ //依次判断0-i的字串能否在wordDict中找到，找到v[i]=true;
                if(v[j] && us.find(s.substr(j,i-j))!=us.end()){
                    v[i]=true;
                }
            }
        }
        return v[n];
    }
};
