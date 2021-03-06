/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Wed 26 Jan 2022 12:16:14 AM CST
    > About:设计循环队列:设计你的循环队列实现。 循环队列是一种线性数据结构，其操作表现基于 FIFO（先进先出）原则并且队尾被连接在队首之后以形成一个循环。它也被称为“环形缓冲器”。

循环队列的一个好处是我们可以利用这个队列之前用过的空间。在一个普通队列里，一旦一个队列满了，我们就不能插入下一个元素，即使在队列前面仍有空间。但是使用循环队列，我们能使用这些空间去存储新的值。

你的实现应该支持如下操作：

MyCircularQueue(k): 构造器，设置队列长度为 k 。
Front: 从队首获取元素。如果队列为空，返回 -1 。
Rear: 获取队尾元素。如果队列为空，返回 -1 。
enQueue(value): 向循环队列插入一个元素。如果成功插入则返回真。
deQueue(): 从循环队列中删除一个元素。如果成功删除则返回真。
isEmpty(): 检查循环队列是否为空。
isFull(): 检查循环队列是否已满。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/design-circular-queue
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<stdio.h>
#include<iostream>
class MyCircularQueue {
public:
    MyCircularQueue(int k) {
        _a=new int[k];
        _cap=k;
        _size=0;
    }

    bool enQueue(int value) {
        if(_size<_cap){
            _a[_size++]=value;
            return true;
        }
        return false;
    }

    bool deQueue() {
        if(_size==0){
            return false;
        }
        int begin=0;
        while(begin<_size-1){
            _a[begin]=_a[begin+1];
            ++begin;
        }
        _size--;
        return true;

    }

    int Front() {
        if(_size==0){
            return -1;
        }
        return _a[0];
    }

    int Rear() {
        if(_size==0){
            return -1;
        }
        return _a[_size-1];
    }

    bool isEmpty() {
        return _size==0;
    }

    bool isFull() {
        return _size==_cap;
    }
private:
    int* _a;
    int _size;
    int _cap;
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */

