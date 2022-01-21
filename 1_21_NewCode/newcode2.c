/*************************************************************************
	> File Name: newcode2.c
	> Author: 
	> Mail: 
	> Created Time: Fri 21 Jan 2022 10:39:13 AM CST
    > About:链表的回文结构:描述
对于一个链表，请设计一个时间复杂度为O(n),额外空间复杂度为O(1)的算法，判断其是否为回文结构。

给定一个链表的头指针A，请返回一个bool值，代表其是否为回文结构。保证链表长度小于等于900。
 ************************************************************************/

#include<iostream>
/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};*/
class PalindromeList {
public:
    bool chkPalindrome(ListNode* A) {
        if(A==nullptr){
            return true;
        }
        std::deque<ListNode*> dq;
        ListNode* cur=A;
        while(cur){
            dq.push_back(cur);
            cur=cur->next;
        }
        while(!dq.empty() || dq.size()>1){
            ListNode* front=dq.front();
            dq.pop_front();
            ListNode* back=dq.back();
            dq.pop_back();
            if(front->val!=back->val){
                return false;
            }
        }
        return true;
    }
};

