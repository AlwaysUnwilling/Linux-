#include<iostream>
#include<stack>
#include<string>

using namespace std;

//32. 最长有效括号:
//给你一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号子串的长度。
//
//暴力解法
class Solution {
public:
    bool IsEfficientBrackets(string& str,int len){
        stack<char> st;
        int start=0;
        while(start<len){
            if(str[start]=='('){
                st.push(str[start]);
            }else{
                if(st.empty()){
                    return false;
                }
                st.pop();
            }
            start++;
        }
        if(st.empty()){
            return true;
        }
        return false;
    }
    int longestValidParentheses(string s) {
       if(s.size()==0 || s.size()==1){
           return 0;
       } 
       int len=s.size();
       if(len%2){
           len-=1;
       }
        int start=0;
        while(start<s.size()){
            string str=s.substr(start,len);
            cout<<str<<endl;
            if(IsEfficientBrackets(str,len)){
                return len;
            }else if(start+1+len<=s.size()){
                start++;
            }else{
                len-=2;
                start=0;
            }
        }
        return 0;
    }
};

//栈:

class Solution {
public:
    int longestValidParentheses(string s) {
        if(s.size()<=1){
            return 0;
        }
        stack<int> st;
        int ret=0;
        st.push(-1);
        int end=0;
        while(end<s.size()){
            if(s[end]=='('){
                st.push(end);
            }else{
                st.pop();
                if(st.empty()){
                    st.push(end);
                }else{
                    ret=max(ret,end-st.top());
                }
            }
            end++;
        }
        return ret;
    }
};

//左右遍历，比较左右括号的个数

class Solution {
public:
    int longestValidParentheses(string s) {
        int left=0,right=0;
        int ret=0;
        for(auto e:s){
            if(e=='('){
                left++;
            }else{
                right++;
            }
            if(left==right){
                ret=max(right*2,ret);
            }else if(right>left){
                left=right=0;
            }
        }
        left=right=0;
        for(int i=s.size()-1;i>=0;--i){
            if(s[i]=='('){
                left++;
            }else{
                right++;
            }
            if(left==right){
                ret=max(ret,right*2);
            }else if(left>right){
                left=right=0;
            }
        }
        return ret;
    }
};
