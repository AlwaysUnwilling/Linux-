/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Mon 24 Jan 2022 11:05:33 AM CST
    > About:复制带随机指针的链表:给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random ，该指针可以指向链表中的任何节点或空节点。

构造这个链表的 深拷贝。 深拷贝应该正好由 n 个 全新 节点组成，其中每个新节点的值都设为其对应的原节点的值。新节点的 next 指针和 random 指针也都应指向复制链表中的新节点，并使原链表和复制链表中的这些指针能够表示相同的链表状态。复制链表中的指针都不应指向原链表中的节点 。

例如，如果原链表中有 X 和 Y 两个节点，其中 X.random --> Y 。那么在复制链表中对应的两个节点 x 和 y ，同样有 x.random --> y 。

返回复制链表的头节点。

用一个由 n 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 [val, random_index] 表示：

val：一个表示 Node.val 的整数。
random_index：随机指针指向的节点索引（范围从 0 到 n-1）；如果不指向任何节点，则为  null 。
你的代码 只 接受原链表的头节点 head 作为传入参数。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/copy-list-with-random-pointer
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<stdio.h>
/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *next;
 *     struct Node *random;
 * };
 */

struct Node* copyRandomList(struct Node* head) {
	if(head==NULL){
        return NULL;
    }
    struct Node* cur=head;
    while(cur){
        struct Node* Next=cur->next;
        struct Node* newNode=malloc(sizeof(struct Node));
        newNode->val=cur->val;
        newNode->random=NULL;
        cur->next=newNode;
        newNode->next=Next;
        cur=Next;
    }
    cur=head;
    while(cur){
        struct Node* newcur=cur->next;
        if(cur->random!=NULL){
            newcur->random=cur->random->next;
        }else{
            newcur->random=NULL;
        }
        cur=cur->next->next;
    }
    struct Node* newhead=head->next;
    struct Node* tail=newhead;
    while(tail){
        struct Node* newNext=tail->next;
        if(newNext==NULL){
            tail->next=NULL;
            break;
        }
        tail->next=newNext->next;
        tail=tail->next;
    }
    return newhead;
}

