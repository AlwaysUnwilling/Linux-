/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Fri 25 Feb 2022 09:58:04 PM CST
    > About:最小栈:设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。

实现 MinStack 类:

MinStack() 初始化堆栈对象。
void push(int val) 将元素val推入堆栈。
void pop() 删除堆栈顶部的元素。
int top() 获取堆栈顶部的元素。
int getMin() 获取堆栈中的最小元素。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/min-stack
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<iostream>
#include<stack>
class MinStack {
public:
    MinStack() {

    }
    
    void push(int val) {
        _st.push(val);
        if(_minst.empty()){
            _minst.push(val);
        }else{
            if(val<=_minst.top()){
                _minst.push(val);
            }
        }
    }
    
    void pop() {
        int val=_st.top();
        _st.pop();
        if(val==_minst.top()){
            _minst.pop();
        }
    }
    
    int top() {
        return _st.top();
    }
    
    int getMin() {
        return _minst.top();
    }
    stack<int> _st;
    stack<int> _minst;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
