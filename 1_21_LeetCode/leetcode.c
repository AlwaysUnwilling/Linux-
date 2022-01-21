/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Fri 21 Jan 2022 10:12:31 AM CST
    > About:合并两个有序链表:将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
 ************************************************************************/

#include<stdio.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2){
    if(list1==NULL){
        return list2;
    }
    if(list2==NULL){
        return list1;
    }
    struct ListNode* Newhead=(struct ListNode*)malloc(sizeof(struct ListNode));
    if(Newhead==NULL){
        exit(-1);
    }
    struct ListNode* cur1=list1;
    struct ListNode* cur2=list2;
    Newhead->next=NULL;
    struct ListNode* tail=Newhead;
    while(cur1 && cur2){
        if(cur1->val>=cur2->val){
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
    struct ListNode* head=Newhead->next;
    free(Newhead);
    return head;
}

