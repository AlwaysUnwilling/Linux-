/*************************************************************************
	> File Name: newcode.c
	> Author: 
	> Mail: 
	> Created Time: Fri 21 Jan 2022 09:54:31 AM CST
    > About:链表中倒数第k个结点:描述
输入一个链表，输出该链表中倒数第k个结点。
 ************************************************************************/

#include<stdio.h>
/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 * };
 *
 * C语言声明定义全局变量请加上static，防止重复定义
 */

/**
 * 
 * @param pListHead ListNode类 
 * @param k int整型 
 * @return ListNode类
 */
struct ListNode* FindKthToTail(struct ListNode* pListHead, int k ) {
    if(pListHead==NULL){
        return NULL;
    }
    struct ListNode* fast=pListHead;
    struct ListNode* slow=pListHead;
    while(k>0){
        fast=fast->next;
        k--;
        if(fast==NULL){
            break;
        }
    }
    if(fast==NULL){
        if(k==0){
            return slow;
        }else{
            return NULL;
        }
    }
    while(fast){
        fast=fast->next;
        slow=slow->next;
    }
    return slow;
}
