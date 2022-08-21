#include<iostream>


//BM4 合并两个排序的链表
/*
 *描述
输入两个递增的链表，单个链表的长度为n，合并这两个链表并使新链表中的节点仍然是递增排序的。
数据范围： 0 \le n \le 10000≤n≤1000，-1000 \le 节点值 \le 1000−1000≤节点值≤1000
要求：空间复杂度 O(1)O(1)，时间复杂度 O(n)O(n)
 * */

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};
class Solution {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
        if(pHead1==nullptr || pHead2==nullptr){
            return pHead1==nullptr?pHead2:pHead1;
        }
        ListNode* head=new ListNode(0);
        auto tail=head;
        auto l1=pHead1,l2=pHead2;
        while(l1 && l2){
            if(l1->val < l2->val){
                tail->next=l1;
                l1=l1->next;
            }else{
                tail->next=l2;
                l2=l2->next;
            }
            tail=tail->next;
        }
        if(l1){
            tail->next=l1;
        }
        if(l2){
            tail->next=l2;
        }
        auto newHead=head->next;
        delete head;
        return newHead;
    }
};

//BM14 链表的奇偶重排
/*
 *描述
给定一个单链表，请设定一个函数，将链表的奇数位节点和偶数位节点分别放在一起，重排后输出。
注意是节点的编号而非节点的数值。

数据范围：节点数量满足 0 \le n \le 10^50≤n≤10 
5
 ，节点中的值都满足 0 \le val \le 10000≤val≤1000
要求：空间复杂度 O(n)O(n)，时间复杂度 O(n)O(n)
 * */

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param head ListNode类 
     * @return ListNode类
     */
    ListNode* oddEvenList(ListNode* head) {
        if(head==nullptr || head->next==nullptr){
            return head;
        }
        ListNode* newHead=new ListNode(0);
        auto tail=newHead;
        auto cur=head;
        int cnt=1;
        queue<ListNode*> q;
        while(cur){
            if(cnt%2){ 
                tail->next=cur;
                tail=tail->next;
            }else{
                q.push(cur);
            }
            cur=cur->next;
            cnt++;
        }
        while(!q.empty()){
            tail->next=q.front();
            q.pop();
            tail=tail->next;
        }
        tail->next=nullptr;
        head=newHead->next;
        delete newHead;
        return head;
        return newHead->next;
    }
};
