/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Sun 16 Jan 2022 07:11:30 PM CST
    > About:移除链表元素：给你一个链表的头节点 head 和一个整数 val ，请你删除链表中所有满足 Node.val == val 的节点，并返回 新的头节点 。
 ************************************************************************/

#include<stdio.h>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* removeElements(struct ListNode* head, int val){
    if(head==NULL){
        return head;
    }
    struct ListNode* sentry=(struct ListNode*)malloc(sizeof(struct ListNode));
    if(sentry==NULL){
        exit(-1);
    }
    sentry->next=head;
    struct ListNode* cur=head;
    struct ListNode* prev=sentry;
    while(cur){
        if(cur->val==val){
            struct ListNode* tmp=cur->next;
            prev->next=tmp;
            free(cur);
            cur=tmp;
        }else{
            prev=cur;
            cur=cur->next;
        }

    }
    head=sentry->next;
    free(sentry);
    sentry=NULL;
    return head;
}

