#include<iostream>
#include<string>

using namespace std;

//BM86 大数加法
/*
 *描述
以字符串的形式读入两个数字，编写一个函数计算它们的和，以字符串形式返回。

数据范围：s.length,t.length \le 100000s.length,t.length≤100000，字符串仅由'0'~‘9’构成
要求：时间复杂度 O(n)O(n)
 * */
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 计算两个数之和
     * @param s string字符串 表示第一个整数
     * @param t string字符串 表示第二个整数
     * @return string字符串
     */
    string solve(string s, string t) {
        // write code here
        if(s.size()==0 || t.size()==0){
            return s.size()==0 ? t:s;
        }
        int index1=s.size()-1;
        int index2=t.size()-1;
        int next=0;
        string ret;
        while(index1>=0 && index2>=0){
            int tmp=s[index1--]-'0'+t[index2--]-'0'+next;
            if(tmp>9){
                next=1;
                tmp-=10;
            }else{
                next=0;
            }
            ret+=tmp+'0';
        }
        while(index1>=0){
            int tmp=s[index1--]-'0'+next;
            if(tmp>9){
                next=1;
                tmp-=10;
            }else{
                next=0;
            }
            ret+=tmp+'0';
        }
        while(index2>=0){
            int tmp=t[index2--]-'0'+next;
            if(tmp>9){
                next=1;
                tmp-=10;
            }else{
                next=0;
            }
            ret+=tmp+'0';
        }
        if(next>0){
            ret+=next+'0';
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
