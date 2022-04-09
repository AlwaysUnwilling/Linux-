#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//剑指 Offer 06. 从尾到头打印链表
//输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。


 //  Definition for singly-linked list.
  struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };
 
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        vector<int> ret;
        if(head==nullptr){
            return ret;
        }
        ListNode* cur=head;
        while(cur){
            ret.push_back(cur->val);
            cur=cur->next;
        }
        reverse(ret.begin(),ret.end());
        return ret;
    }
};

//剑指 Offer 24. 反转链表
//定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution1 {
public:
    ListNode* reverseList(ListNode* head) {
        if(head==nullptr || head->next==nullptr){
            return head;
        }
        ListNode* cur=head;
        ListNode* Prev=nullptr;
        while(cur && cur->next){
            ListNode* Next=cur->next;
            cur->next=Prev;
            Prev=cur;
            cur=Next;
        }
        cur->next=Prev;
        return cur;
    }
};

//剑指 Offer 35. 复杂链表的复制
//请实现 copyRandomList 函数，复制一个复杂链表。在复杂链表中，每个节点除了有一个 next 指针指向下一个节点，还有一个 random 指针指向链表中的任意节点或者 null。

// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution2 {
public:
    Node* copyRandomList(Node* head) {
        if(head==nullptr){
            return nullptr;
        }
        Node* cur=head;
        //link newNode to next to cur
        while(cur){
            Node* Next=cur->next;
            Node* newNode=new Node(cur->val);
            cur->next=newNode;
            newNode->next=Next;
            cur=Next;
        }
        //copy random
        cur=head;
        while(cur){
            Node* Next=cur->next;
            if(cur->random){
                Next->random=cur->random->next;
            }
            cur=Next->next;
        }
        //break up newNode
        cur=head;
        Node* newHead=new Node(0);
        Node* tail=newHead;
        while(cur){
            Node* Next=cur->next;
            tail->next=Next;
            tail=tail->next;
            cur->next=Next->next;
            cur=cur->next;
        }
        //tail->next=nullptr;
        Node* retHead=newHead->next;
        delete newHead;
        return retHead;
    }
};
