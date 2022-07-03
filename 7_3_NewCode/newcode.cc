#include<iostream>
#include<vector>


using namespace std;

//BM5 合并k个已排序的链表
/*
 *描述
合并 k 个升序的链表并将结果作为一个升序的链表返回其头节点。

数据范围：节点总数满足 0 \le n \le 10^50≤n≤10 
5
 ，链表个数满足 1 \le k \le 10^5 \1≤k≤10 
5
   ，每个链表的长度满足 1 \le len \le 200 \1≤len≤200  ，每个节点的值满足 |val| <= 1000∣val∣<=1000
要求：时间复杂度 O(nlogk)O(nlogk)
 * */


//Definition for singly-linked list.
struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* _MergeLists(ListNode* l1,ListNode* l2)
    {
        if(l1==nullptr){
            return l2;
        }
        if(l2==nullptr){
            return l1;
        }
        auto cur1=l1;
        auto cur2=l2;
        ListNode* newHead=new ListNode(0);
        ListNode* tail=newHead;
        while(cur1 && cur2){
            if(cur1->val>cur2->val){
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
        auto head=newHead->next;
        delete newHead;
        return head;
    }
    ListNode* MergeLists(vector<ListNode*>& lists, int left,int right)
    {
        if(left>right){
            return nullptr;
        }else if(left==right){
            return lists[left];
        }
        int mid=(left+right)>>1;
        return _MergeLists(MergeLists(lists,left,mid),MergeLists(lists,mid+1,right));
        
    }
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        if(lists.size()==0){
            return nullptr;
        }
        if(lists.size()==1){
            return lists[0];
        }
        return MergeLists(lists,0,lists.size()-1);
    }
};


//BM3 链表中的节点每k个一组翻转
/*
 *描述
将给出的链表中的节点每 k 个一组翻转，返回翻转后的链表
如果链表中的节点数不是 k 的倍数，将最后剩下的节点保持原样
你不能更改节点中的值，只能更改节点本身。

数据范围： \ 0 \le n \le 2000 0≤n≤2000 ， 1 \le k \le 20001≤k≤2000 ，链表中每个元素都满足 0 \le val \le 10000≤val≤1000
要求空间复杂度 O(1)O(1)，时间复杂度 O(n)O(n)
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
     * @param k int整型 
     * @return ListNode类
     */
    void reverseList(ListNode* list)
    {
        if(list==nullptr || list->next==nullptr){
            return ;
        }
        ListNode* _prev=nullptr;
        ListNode* _cur=list;
        while(_cur){
            ListNode* _next=_cur->next;
            _cur->next=_prev;
            _prev=_cur;
            _cur=_next;
        }
        
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(head==nullptr || head->next==nullptr){
            return head;
        }  
        int n=0;
        ListNode* newHead=(ListNode*)malloc(sizeof(struct ListNode));
        auto tail=newHead;
        tail->next=head;
        auto cur=head;
        auto l=cur;
        ListNode* pre=nullptr;
        while(cur){
            n++;
            if(n==k){
                auto Next=cur->next;
                cur->next=nullptr;
                reverseList(l);
                tail->next=cur;
                l->next=Next;
                tail=l;
                l=l->next;
                n=0;
                cur=Next;
            }else{
                cur=cur->next;  
            }
        }
       head=newHead->next;
      free(newHead);
      return head;
    }
};
