/*************************************************************************
	> File Name: newcode1.c
	> Author: 
	> Mail: 
	> Created Time: Fri 21 Jan 2022 10:26:46 AM CST
    > About:链表分割:描述
现有一链表的头指针 ListNode* pHead，给一定值x，编写一段代码将所有小于x的结点排在其余结点之前，且不能改变原来的数据顺序，返回重新排列后的链表的头指针。
 ************************************************************************/

#include<iostream>


/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};*/
class Partition {
public:
    ListNode* partition(ListNode* pHead, int x) {
        if(pHead==nullptr){
            return nullptr;
        }
        std::queue<ListNode*> q;
        ListNode* NewHead=new ListNode(x);
        ListNode* tail=NewHead;
        ListNode* cur=pHead;
        while(cur){
            if(cur->val<x){
                tail->next=cur;
                tail=tail->next;
            }else{
                q.push(cur);
            }
            cur=cur->next;
        }
        while(!q.empty()){
            tail->next=q.front();
            q.pop();
            tail=tail->next;
        }
        tail->next=nullptr;
        ListNode* head=NewHead->next;
        delete NewHead;
        return head;
    }
};

