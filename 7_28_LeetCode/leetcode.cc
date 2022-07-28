#include<iostream>


using namespace std;

//148. 排序链表
/*
 *给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。
 * */

//自顶向下归并排序：每次把链表l分为了l1和l的最后一个节点的俩个链表

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
    ListNode* mergeList(ListNode* l1,ListNode* l2)
    {
        ListNode* newNode=new ListNode;
        ListNode* tail=newNode;
        ListNode *tmpl1=l1,*tmpl2=l2;
        while(tmpl1 && tmpl2){
            if(tmpl1->val<=tmpl2->val){
                tail->next=tmpl1;
                tmpl1=tmpl1->next;
            }else{
                tail->next=tmpl2;
                tmpl2=tmpl2->next;
            }
            tail=tail->next;
        }
        if(tmpl1){
            tail->next=tmpl1;
        }
        if(tmpl2){
            tail->next=tmpl2;
        }
        ListNode* head=newNode->next;
        delete newNode;
        return head;
    }
    ListNode* _sortLists(ListNode* l1,ListNode* l2)
    {   
        if(l1==nullptr){
            return l1;
        }
        if(l1->next==l2){
            l1->next=nullptr;
            return l1;
        }

        ListNode* fast=l1->next;
        ListNode* slow=l1;
        while(fast!=l2){
            fast=fast->next;
            slow=slow->next;
            if(fast!=l2){
                fast=fast->next;
            }
        }
        ListNode* mid=slow;
        return mergeList(_sortLists(l1,mid),_sortLists(mid,l2));
    }
    ListNode* sortList(ListNode* head) {
        if(head==nullptr || head->next==nullptr){
            return head;
        }
        return _sortLists(head,nullptr);
    }
};

//自底向上归并:链表长度依次为1、2、4、8、16...每次截取的最后一个链表长度可以小于每次的截取长度

class Solution {
public:
    ListNode* mergeList(ListNode* l1,ListNode* l2)
    {
        ListNode* newNode=new ListNode;
        ListNode* tail=newNode;
        ListNode *tmpl1=l1,*tmpl2=l2;
        while(tmpl1 && tmpl2){
            if(tmpl1->val<=tmpl2->val){
                tail->next=tmpl1;
                tmpl1=tmpl1->next;
            }else{
                tail->next=tmpl2;
                tmpl2=tmpl2->next;
            }
            tail=tail->next;
        }
        if(tmpl1){
            tail->next=tmpl1;
        }
        if(tmpl2){
            tail->next=tmpl2;
        }
        ListNode* head=newNode->next;
        delete newNode;
        return head;
    }
    ListNode* sortList(ListNode* head) {
        if(head==nullptr || head->next==nullptr){
            return head;
        }
        int length=0;
        auto cur=head;
        while(cur){
            length++;
            cur=cur->next;
        }
        //创建一个哨兵为头节点记录链表头
        ListNode* newHead=new ListNode;
        newHead->next=head;
        for(int subLen=1;subLen<length;subLen*=2){
            ListNode* tail=newHead;
            cur=newHead->next;
            while(cur!=nullptr){
                //分离第一个长度为subLen的链表l1
                ListNode* head1=cur;
                for(int i=1;i<subLen && cur!=nullptr;++i){
                    cur=cur->next;
                }
                //记录第二个链表l2的表头，即此时cur的next
                ListNode* head2=nullptr;
                if(cur!=nullptr){
                    head2=cur->next;
                    cur->next=nullptr;
                }
                //分离l1和l2
                cur=head2;
                //截取长度为subLen的链表l2
                for(int i=1;i<subLen && cur!=nullptr;++i){
                    cur=cur->next;
                }
                //记录截取俩个链表后的表头(此时可能已经被截取完)
                if(cur!=nullptr){
                    ListNode* Next=cur->next;
                    cur->next=nullptr;//断开l2的末尾指向nullptr
                    cur=Next;
                }
                //归并俩个有序链表l1和l2
                tail->next=mergeList(head1,head2);
                while(tail->next){
                    tail=tail->next;
                }
            }
        }
        head=newHead->next;
        delete newHead;
        return head;
    }
};

