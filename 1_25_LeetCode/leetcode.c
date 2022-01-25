/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Tue 25 Jan 2022 10:15:23 PM CST
    > About:有效的括号:给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/valid-parentheses
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<stdio.h>
#include<iostream>
class Solution {
public:
    bool isValid(string s) {
        if(s.size()==0){
            return false;
        }
        stack<char> st;
        for(int i=0;i<s.size();++i){
            if(s[i]=='('
            || s[i]=='['
            || s[i]=='{'){
                st.push(s[i]);
            }else{
                if(!st.empty()){
                    char ch=st.top();
                    st.pop();
                    switch(ch)
                    {
                        case '(':
                        if(s[i]!=')'){
                            return false;
                        }
                        break;
                        case '[':
                        if(s[i]!=']'){
                            return false;
                        }
                        break;
                        case '{':
                        if(s[i]!='}'){
                            return false;
                        }
                        break;
                    }
                }else{
                    return false;
                }
            }
        }
        if(st.empty()){
            return true;
        }else{
            return false;
        }
    }
};

