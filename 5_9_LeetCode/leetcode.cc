#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
#include<queue>


using namespace std;


//937. 重新排列日志文件
/*
 *给你一个日志数组 logs。每条日志都是以空格分隔的字串，其第一个字为字母与数字混合的 标识符 。

有两种不同类型的日志：

字母日志：除标识符之外，所有字均由小写字母组成
数字日志：除标识符之外，所有字均由数字组成
请按下述规则将日志重新排序：

所有 字母日志 都排在 数字日志 之前。
字母日志 在内容不同时，忽略标识符后，按内容字母顺序排序；在内容相同时，按标识符排序。
数字日志 应该保留原来的相对顺序。
返回日志的最终顺序。
 * */

class Solution {
public:

    bool IsLetterLogs(const string& log)
    {
        size_t index=log.find(' ');
        if(log[index+1]>='0' && log[index+1]<='9'){
            return false;
        }else{
            return true;
        }
    }
    vector<string> reorderLogFiles(vector<string>& logs) {
        if(logs.size()==0 || logs.size()==1){
            return logs;
        }
        for(int i=0;i<logs.size();++i){
            if(!IsLetterLogs(logs[i])){
                int index=i;
                while(index<logs.size() && !IsLetterLogs(logs[index])){
                    index++;
                }
                if(index<logs.size()){
                    string tmp=logs[index];
                    int end=index;
                    while(end>i){
                        logs[end]=logs[end-1];
                        --end;
                    }
                    logs[end]=tmp;
                }
            }
        }
        int size=0;
        for(const auto& e:logs){
            if(IsLetterLogs(e)){
                size++;
            }
        }
        sort(logs.begin(),logs.begin()+size,[&](const string& s1,const string& s2){
            return s1.substr(s1.find(' '))==s2.substr(s2.find(' '))?
                    s1<s2:s1.substr(s1.find(' '))<s2.substr(s2.find(' '));
        });
        return logs;
    }
};


//433. 最小基因变化
/*
 *基因序列可以表示为一条由 8 个字符组成的字符串，其中每个字符都是 'A'、'C'、'G' 和 'T' 之一。

假设我们需要调查从基因序列 start 变为 end 所发生的基因变化。一次基因变化就意味着这个基因序列中的一个字符发生了变化。

例如，"AACCGGTT" --> "AACCGGTA" 就是一次基因变化。
另有一个基因库 bank 记录了所有有效的基因变化，只有基因库中的基因才是有效的基因序列。

给你两个基因序列 start 和 end ，以及一个基因库 bank ，请你找出并返回能够使 start 变化为 end 所需的最少变化次数。如果无法完成此基因变化，返回 -1 。

注意：起始基因序列 start 默认是有效的，但是它并不一定会出现在基因库中。
 * */

class Solution {
public:
    int Distance(const string& s1,const string& s2)
    {
        int cnt=0;
        for(int i=0;i<s1.size();++i){
            if(s1[i]!=s2[i]){
                cnt++;
            }
        }
        return cnt;
    }
    int minMutation(string start, string end, vector<string>& bank) {
        int res=0;
        queue<string> q; //用于存放每次start变化的结果
        map<string,bool> m;//去除已经变换过的序列,不去除可能会导致死循环
        for(const auto& e:bank){
            m[e]=false;
        }
        q.push(start);
        m[start]=true;
        while(!q.empty()){
            int size=q.size();
            for(int i=0;i<size;++i){
                auto gene=q.front();
                q.pop();
                if(gene==end) return res;
                //不相等则需要进行变化：一次变化后的序列必须与gene只有一个字符不同。并且变换后的字符串必须在bank中能找到，且
                //在m中未出现过
                for(const auto& e:bank){
                    if(Distance(gene,e)==1 && m[e]==false){
                        q.push(e);
                        m[e]=true;
                    }
                }
            }
            res++;
        }
        return -1;
    }
};

