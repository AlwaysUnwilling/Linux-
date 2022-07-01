#include<iostream>


using namespace std;

//BM2 链表内指定区间反转
/*
 *描述
将一个节点数为 size 链表 m 位置到 n 位置之间的区间反转，要求时间复杂度 O(n)O(n)，空间复杂度 O(1)O(1)。
例如：
给出的链表为 1\to 2 \to 3 \to 4 \to 5 \to NULL1→2→3→4→5→NULL, m=2,n=4m=2,n=4,
返回 1\to 4\to 3\to 2\to 5\to NULL1→4→3→2→5→NULL.

数据范围： 链表长度 0 < size \le 10000<size≤1000，0 < m \le n \le size0<m≤n≤size，链表中每个节点的值满足 |val| \le 1000∣val∣≤1000
要求：时间复杂度 O(n)O(n) ，空间复杂度 O(n)O(n)
进阶：时间复杂度 O(n)O(n)，空间复杂度 O(1)O(1)
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
     * @param m int整型 
     * @param n int整型 
     * @return ListNode类
     */
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if(m==n){
            return head;
        }
        ListNode* preNode=nullptr;
        ListNode* curNode=head;
        int i=1;
        while(i<m){
            preNode=curNode;
            curNode=curNode->next;
            i++;
        }
        ListNode* newHead=curNode;
        ListNode* Next=curNode->next;
        auto prev=newHead;
        for(int j=m;j<n;++j){
            curNode=Next;
            Next=curNode->next;
            curNode->next=prev;
            prev=curNode;
            
        }
        if(preNode==nullptr){
            head->next=Next;
            return prev;
        }else{
            preNode->next=prev;
            newHead->next=Next;
            return head;
        }
    }
};

//BM9 删除链表的倒数第n个节点
/*
 * 描述
给定一个链表，删除链表的倒数第 n 个节点并返回链表的头指针
例如，
给出的链表为: 1\to 2\to 3\to 4\to 51→2→3→4→5, n= 2n=2.
删除了链表的倒数第 nn 个节点之后,链表变为1\to 2\to 3\to 51→2→3→5.

数据范围： 链表长度 0\le n \le 10000≤n≤1000，链表中任意节点的值满足 0 \le val \le 1000≤val≤100
要求：空间复杂度 O(1)O(1)，时间复杂度 O(n)O(n)
备注：
题目保证 nn 一定是有效的
 * */

class Solution {
public:
    /**
     * 
     * @param head ListNode类 
     * @param n int整型 
     * @return ListNode类
     */
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(head==nullptr){
            return head;
        }
        ListNode* _prev=nullptr;
        ListNode* _next=head;
        ListNode* _cur=head;
        while(n--){
            _next=_next->next;
        }
        while(_next){
            _next=_next->next;
            _prev=_cur;
            _cur=_cur->next;
        }
        if(_prev==nullptr){
            auto newHead=head->next;
            delete head;
            return newHead;
        }
        auto Next=_cur->next;
        _prev->next=Next;
        delete _cur;
        return head;
    }
};
