#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//473. 火柴拼正方形
/*
 *你将得到一个整数数组 matchsticks ，其中 matchsticks[i] 是第 i 个火柴棒的长度。你要用 所有的火柴棍 拼成一个正方形。你 不能折断 任何一根火柴棒，但你可以把它们连在一起，而且每根火柴棒必须 使用一次 。

如果你能使这个正方形，则返回 true ，否则返回 false 。
 * */

class Solution {
public:
    bool CanBuildSquare(vector<int>& matchsticks,vector<int>& edge,int index,int side)
    {
        if(index==matchsticks.size()){
            return true;
        }
        for(int i=0;i<edge.size();++i){
            edge[i]+=matchsticks[index];
            if(edge[i]<=side && CanBuildSquare(matchsticks,edge,index+1,side)){
                return true;
            }
            edge[i]-=matchsticks[index];
        }
        return false;
    }
    bool makesquare(vector<int>& matchsticks) {
        if(matchsticks.size()<4){
            return false;
        }
        int side=0;
        for(auto& e:matchsticks){
            side+=e;
        }
        if(side%4){
            return false;
        }
        side/=4;
        sort(matchsticks.begin(),matchsticks.end(),greater<int>());
        vector<int> edge(4);
        return CanBuildSquare(matchsticks,edge,0,side);
    }
};

//剑指 Offer 20. 表示数值的字符串
/*
 *请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。

数值（按顺序）可以分成以下几个部分：

若干空格
一个 小数 或者 整数
（可选）一个 'e' 或 'E' ，后面跟着一个 整数
若干空格
小数（按顺序）可以分成以下几个部分：

（可选）一个符号字符（'+' 或 '-'）
下述格式之一：
至少一位数字，后面跟着一个点 '.'
至少一位数字，后面跟着一个点 '.' ，后面再跟着至少一位数字
一个点 '.' ，后面跟着至少一位数字
整数（按顺序）可以分成以下几个部分：

（可选）一个符号字符（'+' 或 '-'）
至少一位数字
部分数值列举如下：

["+100", "5e2", "-123", "3.1416", "-1E-16", "0123"]
部分非数值列举如下：

["12e", "1a3.14", "1.2.3", "+-5", "12e+5.4"]
 * */


class Solution {
public:
    bool isIntNumOrFloatNum(string& str)
    {
        int cpoint=0;
        int eCount=0;
        for(int i=0;i<str.size();++i){
            if(str[i]=='+' || str[i]=='-'){
                if(i+1<str.size() && (str[i+1]=='+' || str[i+1]=='-')){
                    return false;
                }else if(i+1>=str.size()){
                    return false;
                }
                if(i-1>=0 && (str[i-1]!='e' && str[i-1]!='E')){
                    return false;
                }
            }else if(str[i]=='e' || str[i]=='E'){
                eCount++;
                if(eCount>1){
                    return false;
                }
                if(i-1<0){
                    return false;
                }else if(str[i-1]=='.' && i-2<0){
                    return false;
                }else if(str[i-1]!='.' && (str[i - 1] < '0' || str[i - 1]>'9')){
                    return false;
                }else if(i+1>=str.size()){
                    return false;
                }else if(str.find('.',i+1)!=string::npos){
                    return false;
                }else if((str[i+1]!='+' && str[i+1]!='-') && (str[i+1]<0 || str[i+1]>'9')){
                    return false;
                }
            }else if(str[i]=='.'){
                cpoint++;
                if(cpoint>=2){
                    return false;
                }else if(i+1<str.size() && ((str[i+1]!='e' && str[i+1]!='E') && ( str[i+1]<'0' || str[i+1]>'9'))){
                    return false;
                }else if(i+1>=str.size() && i-1>=0 && (str[i-1]=='+' || str[i-1]=='-')){
                    return false;
                }
            }else if(str[i]<'0' || str[i]>'9'){
                return false;
            }
        }
        return true;
    }
    bool isNumber(string s) {
        if(s.size()==0){
            return false;
        }
        string str;
        int begin=0,end=0;
        for(int i=0;i<s.size();++i){
            if(s[i]!=' '){
                begin=i;
                break;
            }
        }
        for(int i=s.size()-1;i>=0;--i){
            if(s[i]!=' '){
                end=i;
                break;
            }
        }
        if(end<begin){
            return false;
        }
        str=s.substr(begin,end-begin+1);
        if(str.size()==1 && (str[0]<'0' || str[0]>'9')){
            return false;
        }
    
        return isIntNumOrFloatNum(str);
    }
};
