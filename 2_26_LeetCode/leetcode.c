/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Sat 26 Feb 2022 08:45:53 PM CST
    > About: 逆波兰表达式求值:根据 逆波兰表示法，求表达式的值。

有效的算符包括 +、-、*、/ 。每个运算对象可以是整数，也可以是另一个逆波兰表达式。

注意 两个整数之间的除法只保留整数部分。

可以保证给定的逆波兰表达式总是有效的。换句话说，表达式总会得出有效数值且不存在除数为 0 的情况。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/evaluate-reverse-polish-notation
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<iostream>
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<string> st;
        for(auto e:tokens){
            if(e!="+" && e!="-" && e!="*" && e!="/"){
                st.push(e);
            }else{
                int x=std::atoi(st.top().c_str());
                st.pop();
                int y=std::atoi(st.top().c_str());
                st.pop();
                char ch=e[0];
                switch(ch){
                    case '+':
                        st.push(to_string(x+y));
                        break;
                    case '-':
                        st.push(to_string(y-x));
                        break;
                    case '*':
                        st.push(to_string(x*y));
                        break;
                    case '/':
                        st.push(to_string(y/x));
                        break;
                }
            }
        }
        string ret=st.top();
        st.pop();
        return atoi(ret.c_str());
    }
};
