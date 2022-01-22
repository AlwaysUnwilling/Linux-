/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Sat 22 Jan 2022 11:09:49 AM CST
    > About:相交链表:给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 null 。
 ************************************************************************/

#include<stdio.h>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    if(headA==NULL || headB==NULL){
        return NULL;
    }
    if(headB==headA){
        return headA;
    }
    struct ListNode* curA=headA;
    struct ListNode* curB=headB;
    int lengthA=0;
    int lengthB=0;
    while(curA){
        curA=curA->next;
        lengthA++;
    }
    while(curB){
        curB=curB->next;
        lengthB++;
    }
    int difval=abs(lengthB-lengthA);
    struct ListNode* fast=headA;
    struct ListNode* slow=headB;
    if(lengthA<lengthB){
        fast=headB;
        slow=headA;
    }
    while(difval){
        difval--;
        fast=fast->next;
    }
    while(slow){
        if(slow==fast){
            return slow;
        }
        slow=slow->next;
        fast=fast->next;
    }
    return NULL;    
}
