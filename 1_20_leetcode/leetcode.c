/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Thu 20 Jan 2022 12:00:48 PM CST
    > About:反转链表:给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
 ************************************************************************/

#include<stdio.h>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseList(struct ListNode* head){
    if(head==NULL || head->next==NULL){
        return head;
    }   
    struct ListNode* Cur=head;
    struct ListNode* Prev=NULL;
    struct ListNode* Next=Cur->next;
    while(Cur){
        Cur->next=Prev;
        Prev=Cur;
        Cur=Next;
        if(Cur==NULL){
           break;   
        }
        Next=Cur->next;
    }
    return Prev;
}

