/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Sun 23 Jan 2022 10:29:41 AM CST
    > About:对链表进行插入排序:插入排序的动画演示如上。从第一个元素开始，该链表可以被认为已经部分排序（用黑色表示）。
每次迭代时，从输入数据中移除一个元素（用红色表示），并原地将其插入到已排好序的链表中。

 

插入排序算法：

插入排序是迭代的，每次只移动一个元素，直到所有元素可以形成一个有序的输出列表。
每次迭代中，插入排序只从输入数据中移除一个待排序的元素，找到它在序列中适当的位置，并将其插入。
重复直到所有输入数据插入完为止。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/insertion-sort-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<stdio.h>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* insertionSortList(struct ListNode* head){
    if(head==NULL || head->next==NULL){
        return head;
    }
    struct ListNode* Cur=head->next;
    struct ListNode* Next=Cur->next;
    head->next=NULL;
    while(Cur){
        if(Cur->val<=head->val){
            Cur->next=head;
            head=Cur;   
        }else{
            struct ListNode* tail=head;
            struct ListNode* prev=NULL;
            while(Cur->val>tail->val){
                prev=tail;
                tail=tail->next;
                if(tail==NULL){
                    prev->next=Cur;
                    prev=prev->next;
                    prev->next=NULL;
                    break;
                }
            }
            if(tail!=NULL){
                prev->next=Cur;
                Cur->next=tail;
            }
        }
        Cur=Next;
        if(Cur==NULL){
            break;
        }else{
            Next=Cur->next;
        }
    }
    return head;
}
