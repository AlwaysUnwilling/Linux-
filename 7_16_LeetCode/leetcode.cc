#include<iostream>
#include<deque>

using namespace std;

//剑指 Offer II 041. 滑动窗口的平均值
/*
 *给定一个整数数据流和一个窗口大小，根据该滑动窗口的大小，计算滑动窗口里所有数字的平均值。

实现 MovingAverage 类：

MovingAverage(int size) 用窗口大小 size 初始化对象。
double next(int val) 成员函数 next 每次调用的时候都会往滑动窗口增加一个整数，请计算并返回数据流中最后 size 个值的移动平均值，即滑动窗口里所有数字的平均值。
 * */
class MovingAverage {
public:
    /** Initialize your data structure here. */
    MovingAverage(int size) {
        capacity=size;
    }
    int GetSum()
    {
        int sum=0;
        for(const auto& e:dq){
            sum+=e;
        }
        return sum;
    }
    double next(int val) {
        if(capacity>dq.size()){
            dq.push_back(val);
            return (double)1.0*GetSum()/dq.size();
        }else{
            dq.pop_front();
            dq.push_back(val);
            return (double)1.0*GetSum()/capacity;
        }
    }
private:
    deque<int> dq;
    int capacity;
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */


//23. 合并K个升序链表
/*
 *给你一个链表数组，每个链表都已经按升序排列。

请你将所有链表合并到一个升序链表中，返回合并后的链表。
 * */

#include<vector>

//Definition for singly-linked list.
struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
class Solution {
public:
    ListNode* ListsSum(ListNode* l1,ListNode* l2)
    {
        if(l1==nullptr || l2==nullptr){
            return l1==nullptr?l2:l1;
        }
        ListNode* cur1=l1;
        ListNode* cur2=l2;
        ListNode* head=new ListNode;
        ListNode* tail=head;
        while(cur1 && cur2){
            if(cur1->val > cur2->val){
                tail->next=cur2;
                cur2=cur2->next;
            }else{
                tail->next=cur1;
                cur1=cur1->next;
            }
            tail=tail->next;
        }
        if(cur1){
            tail->next=cur1;
        }
        if(cur2){
            tail->next=cur2;
        }
        auto newHead=head->next;
        delete head;
        return newHead;
    }
    ListNode* _mergeKLists(vector<ListNode*>& lists,int left,int right)
    {
        if(left>right){
            return nullptr;
        }
        if(left==right){
            return lists[left];
        }
        int mid=(left+right)>>1;

        return ListsSum(_mergeKLists(lists,left,mid),_mergeKLists(lists,mid+1,right));
    }
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size()==0){
            return nullptr;
        }
        if(lists.size()==1){
            return lists[0];
        }
        return _mergeKLists(lists,0,lists.size()-1);
    }
};
