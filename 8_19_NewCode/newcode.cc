#include<iostream>

using namespace std;

//BM10 两个链表的第一个公共结点
/*
 *输入两个无环的单向链表，找出它们的第一个公共结点，如果没有公共节点则返回空。（注意因为传入数据是链表，所以错误测试数据的提示是用其他方式显示的，保证传入数据是正确的）

数据范围： n \le 1000n≤1000
要求：空间复杂度 O(1)O(1)，时间复杂度 O(n)O(n)
 * */

//双指针：俩个指针同时从phead1和phead2出发走完俩个链表，如果有公共节点则会在第一个公共节点相遇。否则会同时走完俩个
//链表且为nullptr
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};
class Solution {
public:
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        if(pHead1==nullptr || pHead2==nullptr){
            return nullptr;
        }
        auto cur1=pHead1;
        auto cur2=pHead2;
        while(cur1!=cur2){
            if(cur1){
                cur1=cur1->next;
            }else{
                cur1=pHead2;
            }
            if(cur2){
                cur2=cur2->next;
            }else{
                cur2=pHead1;
            }
        }
        return cur1;
    }
};

//BM12 单链表的排序
/*
 *描述
给定一个节点数为n的无序单链表，对其按升序排序。

数据范围：0 < n \le 1000000<n≤100000
要求：时间复杂度 O(nlogn)O(nlogn)<Paste>
 * */
class Solution {
public:
    /**
     * 
     * @param head ListNode类 the head node
     * @return ListNode类
     */
    ListNode* sortInList(ListNode* head) {
        if(head==nullptr || head->next==nullptr){
            return head;
        }
        ListNode* newHead=(struct ListNode*)malloc(sizeof(struct ListNode));
        newHead->next=head;
        auto cur=head->next;
        head->next=nullptr;
        while(cur){
            auto Next=cur->next;
            auto node=newHead->next;
            auto prev=newHead;
            while(node && node->val < cur->val){
                prev=node;
                node=node->next;
            }
            prev->next=cur;
            cur->next=node;
            cur=Next;
        }
        head=newHead->next;
        free(newHead);
        newHead=nullptr;
        return head;
    }
};
