#include<iostream>
#include<stack>

using namespace std; 

//剑指 Offer 09. 用两个栈实现队列
//用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead ，分别完成在队列尾部插入整数和在队列头部删除整数的功能。(若队列中没有元素，deleteHead 操作返回 -1 )
class CQueue {
public:
    CQueue() {

    }
    
    void appendTail(int value) {
        if(st1.empty() && st2.empty()){
            st1.push(value);
        }else if(!st1.empty()){
            st1.push(value);
        }else{
            st2.push(value);
        }
    }
    
    int deleteHead() {
        if(st1.empty() && st2.empty()){
            return -1;
        }
        int top=0;
        if(!st1.empty()){
            while(!st1.empty()){
                st2.push(st1.top());
                st1.pop();
            }
            top=st2.top();
            st2.pop();
            while(!st2.empty()){
                st1.push(st2.top());
                st2.pop();
            }
        }
        if(!st2.empty()){
            while(!st2.empty()){
                st1.push(st2.top());
                st2.pop();
            }
                top=st1.top();
            st1.pop();
            while(!st1.empty()){
                st2.push(st1.top());
                st1.pop();
            }
        }
        return top;
    }
private:
    stack<int> st1;
    stack<int> st2;
};
/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */ 

//剑指 Offer 30. 包含min函数的栈
//定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的 min 函数在该栈中，调用 min、push 及 pop 的时间复杂度都是 O(1)。

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {

    }
    
    void push(int x) {
        if(minValue.empty()){
            minValue.push(x);
        }else{
            if(x<=minValue.top()){
                minValue.push(x);
            }
        }
        st.push(x);
    }
    
    void pop() {
        assert(!st.empty());
        if(st.top()==minValue.top()){
            minValue.pop();
        }
        st.pop();
    }
    
    int top() {
        return st.top();
    }
    
    int min() {
        return minValue.top();
    }
private:
    stack<int> minValue;
    stack<int> st;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->min();
 */ 
