//串联所有单词的子串:
//给定一个字符串 s 和一些 长度相同 的单词 words 。找出 s 中恰好可以由 words 中所有单词串联形成的子串的起始位置。
//注意子串要与 words 中的单词完全匹配，中间不能有其他字符 ，但不需要考虑 words 中单词串联的顺序 

#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<map>

using namespace std;

class Solution
{
public:
	bool IsAllWordsMatched(map<string,int>& tmp)
	{
  	for(auto& e:tmp){
    	if(e.second>0){
      	return false;
      }
    }
 		return true;              
  }
	bool IsAllWordsUsed(map<string,int>& tmp)
  {
    for(auto& e:tmp){
      if(e.second!=0){
      	return false;
      }
    }
    return true;
  }
  vector<int> findSubstring(string s, vector<string>& words) {
  	int length=words[0].size();
    set<int> st;
   	vector<int> ret;
   	map<string,int> m;
   	for(auto& e:words){
   		m[e]++;
    }
   	for(auto& e:m){
  		int pos=0;
      int i=0;
      while((i=s.find(e.first,pos))!=string::npos){
      	int index=i;
      	map<string,int> tmp=m;
      	while(index<s.size()){
        	string strtmp;
          int size=length;
        	while(index<s.size() && size--){
       			strtmp+=s[index++];
          }
       		auto it=tmp.find(strtmp);
        	if(it!=tmp.end()){
          	tmp[strtmp]--;
           	if(IsAllWordsMatched(tmp)){
          		break;
            }
         	}else{
          	break;
         	}
       }
 				if(IsAllWordsUsed(tmp)){
      		st.insert(i);
      	}
  			pos++;
    	}
    }
    for(auto& e:st){
    	ret.push_back(e);
		}
    return ret;
  }
};
