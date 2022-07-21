#include<iostream>
#include<vector>

using namespace std;

//148. 排序链表
/*
 *给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。
 * */

//Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(head==nullptr || head->next==nullptr){
            return head;
        }
        ListNode* newHead=new ListNode;
        newHead->next=head;
        ListNode* cur=head->next;
        ListNode* prev=head;
        while(cur){
            ListNode* Next=cur->next;
            if(cur->val < newHead->next->val){
                prev->next=Next;
                auto tail=newHead->next;
                newHead->next=cur;
                cur->next=tail;
            }else{
                auto tail=newHead->next;
                auto preTail=newHead;
                while(tail!=cur && tail->val <= cur->val){
                    preTail=tail;
                    tail=tail->next;
                }
                if(cur==tail){
                    prev=cur;
                }else{
                    preTail->next=cur;
                    cur->next=tail;

                    prev->next=Next;
                }
            }
            cur=Next;
        }
        head=newHead->next;
        delete newHead;
        return head;
    }
};

//169. 多数元素
/*
 *给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。
 * */

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        if(nums.size()==1){
            return nums[0];
        }
        int ret=0;
        int cnt=0;
        for(const auto& num:nums){
            if(!cnt){
                ret=num;
                cnt=1;
            }else{
                if(num==ret){
                    cnt++;
                }else{
                    cnt--;
                }
            }
        }
        return ret;
    }
};
