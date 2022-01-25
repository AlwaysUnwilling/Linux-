/*************************************************************************
	> File Name: leetcode1.c
	> Author: 
	> Mail: 
	> Created Time: Tue 25 Jan 2022 10:46:58 PM CST
    > About:用队列实现栈:请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作（push、top、pop 和 empty）。

实现 MyStack 类：

void push(int x) 将元素 x 压入栈顶。
int pop() 移除并返回栈顶元素。
int top() 返回栈顶元素。
boolean empty() 如果栈是空的，返回 true ；否则，返回 false 。
 

注意：

你只能使用队列的基本操作 —— 也就是 push to back、peek/pop from front、size 和 is empty 这些操作。
你所使用的语言也许不支持队列。 你可以使用 list （列表）或者 deque（双端队列）来模拟一个队列 , 只要是标准的队列操作即可。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/implement-stack-using-queues
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<stdio.h>
#include<iostream>
class MyStack {
public:
    MyStack() {

    }

    void push(int x) {
        if(!q1.empty()){
            q1.push(x);
        }else{
            q2.push(x);
        }
    }

    int pop() {
        if(q1.empty()){
            if(q2.size()==1){
                int top=q2.front();
                q2.pop();
                return top;
            }
            while(q2.size()>1){
                q1.push(q2.front());
                q2.pop();
            }
            int top=q2.front();
            q2.pop();
            return top;
        }else{
            if(q1.size()==1){
                int top=q1.front();
                q1.pop();
                return top;
            }
            while(q1.size()>1){
                q2.push(q1.front());
                q1.pop();
            }
            int top=q1.front();
            q1.pop();
            return top;
        }
    }

    int top() {
        if(q1.empty()){
            return q2.back();
        }else{
            return q1.back();
        }
    }

    bool empty() {
        return q1.empty() && q2.empty();
    }
private:
    queue<int> q1;
    queue<int> q2;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

