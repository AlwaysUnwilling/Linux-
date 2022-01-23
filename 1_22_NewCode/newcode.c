/*************************************************************************
	> File Name: newcode.c
	> Author: 
	> Mail: 
	> Created Time: Sat 22 Jan 2022 12:17:13 PM CST
    > About:删除链表中重复的结点:描述
在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。 例如，链表 1->2->3->3->4->4->5  处理后为 1->2->5

数据范围：链表长度满足 0 \le n \le 1000 \0≤n≤1000  ，链表中的值满足 1 \le val \le 1000 \1≤val≤1000 

进阶：空间复杂度 O(n)\O(n)  ，时间复杂度 O(n) \O(n)
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
 * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
 *
 *
 * @param pHead ListNode类
 * @return ListNode类
 */
struct ListNode* deleteDuplication(struct ListNode* pHead ) {
    if(pHead==NULL || pHead->next==NULL){
        return pHead;
    }
    struct ListNode* NewHead=(struct ListNode*)malloc(sizeof(struct ListNode));
    if(NewHead==NULL){
        exit(-1);
    }
    NewHead->next=NULL;
    struct ListNode* tail=NewHead;
    struct ListNode* Cur=pHead;
    struct ListNode* Next=Cur->next;
    while(Cur && Next){
        if(Cur->val==Next->val){
            while(Cur->val==Next->val){
                Next=Next->next;
                if(Next==NULL){
                    while(Cur){
                        struct ListNode* tmp=Cur->next;
                        free(Cur);
                        Cur=tmp;
                    }
                    break;
                }
            }
            if(Next!=NULL){
                while(Cur!=Next){
                    struct ListNode* tmp=Cur->next;
                    free(Cur);
                    Cur=tmp;
                }
                Next=Cur->next;
            }
        }else{
            tail->next=Cur;
            tail=tail->next;
            Cur=Next;
            Next=Cur->next;
        }
    }
    if(Cur){
        tail->next=Cur;
        tail=tail->next;
        tail->next=NULL;
    }else{
        tail->next=NULL;
    }

    struct ListNode* head=NewHead->next;
    free(NewHead);
    return head;
}

