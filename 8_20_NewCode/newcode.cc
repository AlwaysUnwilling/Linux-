#include<iostream>

//BM15 删除有序链表中重复的元素-I
/*
 *描述
删除给出链表中的重复元素（链表中元素从小到大有序），使链表中的所有元素都只出现一次
 * */

 struct ListNode {
	int val;
	struct ListNode *next;
 };

class Solution {
public:
    /**
     * 
     * @param head ListNode类 
     * @return ListNode类
     */
    ListNode* deleteDuplicates(ListNode* head) {
        if(head==nullptr || head->next==nullptr){
            return head;
        }
        ListNode* newHead=(ListNode*)malloc(sizeof(struct ListNode));
        newHead->next=head;
        auto _cur=head;
        auto _prev=newHead;
        auto _next=_cur->next;
        while(_next){
            if(_cur->val == _next->val){
                while(_next && _cur->val == _next->val){
                    _next=_next->next;           
                } 
                _prev=_cur;
                _cur=_cur->next;
                while(_cur && _cur!=_next){
                    _cur=_cur->next;
                }
                _prev->next=_next;
                if(_next==nullptr){
                    break;
                }
                _cur=_next;
                _next=_next->next;
            }else{
                _prev=_cur;
                _cur=_next;
                _next=_next->next;
            }

        }
        head=newHead->next;
        free(newHead);
        newHead=nullptr;
        return head;
    }
};
