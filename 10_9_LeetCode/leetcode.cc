#include<iostream>
#include<vector>
#include<string>


/*
 *最长公共前缀
  编写一个函数来查找字符串数组中的最长公共前缀。
如果不存在公共前缀，返回空字符串 ""。
 * */

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int num=strs.size();
        if(num==0 || num==1)
        {
            return num==0?"":strs[0];
        }

        string ans;
        bool flag=true;
        for(int i = 0;i < strs[0].size();++i)
        {
            char tmp=strs[0][i];
            ans+=tmp;
            for(int j= 1;j < num;++j)
            {
                if(i >= strs[j].size() || strs[j][i] != tmp)
                {
                    flag=false;
                    ans.pop_back();
                    break;
                }
            }
            if(!flag)
            {
                break;
            }
        }
        return ans;
    }
};


/*
 *罗马数字转整数
 罗马数字包含以下七种字符: I， V， X， L，C，D 和 M。
 * */
class Solution {
public:
    int romanToInt(string s) {
        int ans=0;
        int tmp=0;
        if(s.size()==0)
        {
            return 0;
        }
        int size=s.size();
        for(int i = 0;i < size;++i)
        {
            switch(s[i])
            {
                case 'I':
                    if(i+1 < size && s[i+1]=='V')
                    {
                        ans+=4;
                        i++;
                    }
                    else if(i+1 < size && s[i+1]=='X')
                    {
                        ans+=9;
                        i++;
                    }
                    else
                    {
                        ans++;
                    }
                break;
                case 'V':
                    ans+=5;
                break;
                case 'X':
                    if(i+1 < size && s[i+1]=='L')
                    {
                        ans+=40;
                        i++;
                    }
                    else if(i+1 < size && s[i+1]=='C')
                    {
                        ans+=90;
                        i++;
                    }
                    else
                    {
                        ans+=10;
                    }
                break;
                case 'L':
                    ans+=50;
                break;
                case 'C':
                    if(i+1 < size && s[i+1]=='D')
                    {
                        ans+=400;
                        i++;
                    }
                    else if(i+1 < size && s[i+1]=='M')
                    {
                        ans+=900;
                        i++;
                    }
                    else
                    {
                        ans+=100;
                    }
                break;
                case 'D':
                    ans+=500;
                break;
                case 'M':
                    ans+=1000;
                break;
                default:
                break;
            }
        }
        return ans;
    }
};
