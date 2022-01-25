/*************************************************************************
	> File Name: leetcode2.c
	> Author: 
	> Mail: 
	> Created Time: Tue 25 Jan 2022 11:02:45 PM CST
    > About:用栈实现队列:请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（push、pop、peek、empty）：

实现 MyQueue 类：

void push(int x) 将元素 x 推到队列的末尾
int pop() 从队列的开头移除并返回元素
int peek() 返回队列开头的元素
boolean empty() 如果队列为空，返回 true ；否则，返回 false
说明：

你 只能 使用标准的栈操作 —— 也就是只有 push to top, peek/pop from top, size, 和 is empty 操作是合法的。
你所使用的语言也许不支持栈。你可以使用 list 或者 deque（双端队列）来模拟一个栈，只要是标准的栈操作即可。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/implement-queue-using-stacks
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<stdio.h>
#include<iostream>
class MyQueue {
public:
    MyQueue() {

    }

    void push(int x) {
        st1.push(x);
    }

    int pop() {
        if(st1.size()==1){
            int front=st1.top();
            st1.pop();
            return front;
        }
        while(st1.size()>1){
            st2.push(st1.top());
            st1.pop();
        }
        int front=st1.top();
        st1.pop();
        while(!st2.empty()){
            st1.push(st2.top());
            st2.pop();
        }
        return front;
    }

    int peek() {
        if(st1.size()==1){
            return st1.top();
        }
        while(!st1.empty()){
            st2.push(st1.top());
            st1.pop();
        }
        int front=st2.top();
        while(!st2.empty()){
            st1.push(st2.top());
            st2.pop();
        }
        return front;
    }

    bool empty() {
        return st1.empty();
    }
private:
    stack<int> st1;  //push
    stack<int> st2;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

