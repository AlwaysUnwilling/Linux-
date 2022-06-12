#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>


using namespace std;

//890. 查找和替换模式
/*
 *你有一个单词列表 words 和一个模式  pattern，你想知道 words 中的哪些单词与模式匹配。

如果存在字母的排列 p ，使得将模式中的每个字母 x 替换为 p(x) 之后，我们就得到了所需的单词，那么单词与模式是匹配的。

（回想一下，字母的排列是从字母到字母的双射：每个字母映射到另一个字母，没有两个字母映射到同一个字母。）

返回 words 中与给定模式匹配的单词列表。

你可以按任何顺序返回答案。
 * */

class Solution {
public:
    bool isMatched(const string& str1,const string& str2)
    {
        if(str1.size()!=str2.size()){
            return false;
        }
        unordered_map<char,char> strMap;
        for(int i=0;i<str1.size();++i){
            if(strMap.find(str1[i])==strMap.end()){
                strMap[str1[i]]=str2[i];
            }else if(strMap[str1[i]]!=str2[i]){
                return false;
            }
        }
        return true;
    }
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        if(words.size()==0 || pattern.size()==0){
            return {};
        }
        vector<string> res;
        for(const auto& e:words){
            if(isMatched(e,pattern) && isMatched(pattern,e)){
                res.push_back(e);
            }
        }
        return res;
    }
};

//剑指 Offer 59 - II. 队列的最大值
/*
 *请定义一个队列并实现函数 max_value 得到队列里的最大值，要求函数max_value、push_back 和 pop_front 的均摊时间复杂度都是O(1)。

若队列为空，pop_front 和 max_value 需要返回 -1
 * */
#include<queue>
#include<deque>

class MaxQueue {
public:
    MaxQueue() {

    }
    
    int max_value() {
        if(maxList.empty()){
            return -1;
        }

        return maxList.front();
    }
    
    void push_back(int value) {
        q.push(value);
        while(!maxList.empty() && maxList.back()<value){
            maxList.pop_back();
        }
        maxList.push_back(value);
    }
    
    int pop_front() {
        if(q.empty()){
            return -1;
        }
        int front=q.front();
        q.pop();
        if(front==maxList.front()){
            maxList.pop_front();
        }
        return front;
    }
private:
    deque<int> maxList;
    queue<int> q;
};

/**
 * Your MaxQueue object will be instantiated and called as such:
 * MaxQueue* obj = new MaxQueue();
 * int param_1 = obj->max_value();
 * obj->push_back(value);
 * int param_3 = obj->pop_front();
 */
