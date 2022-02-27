/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Sun 27 Feb 2022 11:01:10 PM CST
    > About:前K个高频单词:给定一个单词列表 words 和一个整数 k ，返回前 k 个出现次数最多的单词。

返回的答案应该按单词出现频率由高到低排序。如果不同的单词有相同出现频率， 按字典顺序 排序。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/top-k-frequent-words
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<iostream>
#include<map>
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        vector<string> vs;
        if(words.size()==0 || k>words.size()){
            return vs;
        }
        map<string,int> m;
        for(auto e:words){
            m[e]++;
        }
        multimap<int,string,greater<int>> ret;
        for(auto e:m){
            ret.insert(make_pair(e.second,e.first));
        }
        auto it=ret.begin();
        while(it!=ret.end() && k--){
            vs.push_back(it->second);
            ++it;
        }
        return vs;
    }
};
