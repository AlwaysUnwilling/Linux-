/*************************************************************************
	> File Name: leetcode1.c
	> Author: 
	> Mail: 
	> Created Time: Fri 25 Feb 2022 11:01:39 PM CST
    > About:栈的压入、弹出序列:描述
输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。
1. 0<=pushV.length == popV.length <=1000
2. -1000<=pushV[i]<=1000
3. pushV 的所有数字均不相同
 ************************************************************************/

#include<iostream>
#include<stack>
class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        stack<int> st;
        size_t end=0;
        for(auto epop:popV){
            while(end<pushV.size()){
                if(epop!=pushV[end]){
                    if(st.empty() || st.top()!=epop){
                        st.push(pushV[end++]);
                    }else{
                        st.pop();
                        break;
                    }
                }else{
                    ++end;
                    break;
                }
            }
            
            if(!st.empty() && st.top()==epop){
                st.pop();
            }
        }
        return st.empty();
    }
};
