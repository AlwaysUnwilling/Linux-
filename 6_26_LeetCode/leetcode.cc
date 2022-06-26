#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>

using namespace std;

//710. 黑名单中的随机数
/*
 *给定一个整数 n 和一个 无重复 黑名单整数数组 blacklist 。设计一种算法，从 [0, n - 1] 范围内的任意整数中选取一个 未加入 黑名单 blacklist 的整数。任何在上述范围内且不在黑名单 blacklist 中的整数都应该有 同等的可能性 被返回。

优化你的算法，使它最小化调用语言 内置 随机函数的次数。

实现 Solution 类:

Solution(int n, int[] blacklist) 初始化整数 n 和被加入黑名单 blacklist 的整数
int pick() 返回一个范围为 [0, n - 1] 且不在黑名单 blacklist 中的随机整数
 * */

//数组 //超时
class Solution {
public:
    Solution(int n, vector<int>& blacklist) {
        unordered_set<int> bl;
        for(const auto& num:blacklist){
            bl.insert(num);
        }
        for(int i=0;i<n;++i){
            if(bl.find(i)==bl.end()){
                PickArr.push_back(i);
            }
        }
    }
    
    int pick() {
        int index=rand()%PickArr.size();
        return PickArr[index];
    }
private:
    vector<int> PickArr;
};

/*
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(n, blacklist);
 * int param_1 = obj->pick();
*/ 

//黑名单映射

class Solution {
public:
    Solution(int n, vector<int>& blacklist) {
        int size=blacklist.size();
        edge=n-size;
        unordered_set<int> black;
        //所有大于edge的黑名单数字都入black
        for(const int& num:blacklist){
            if(num>=edge){
                black.insert(num);
            }
        }
        //所有小于edge的数字：如果是白名单数字则不动；黑名单数字映射到whileNum从edge开始一直++
        //直到whileNum不在黑名单中为止。即[0-edge)的所有黑名单数字都可以在[edge,n)上找到对应的
        //白名单数字(所有数字)
        int whileNum=edge;
        for(const int& e:blacklist){
            if(e<edge){
                while(black.count(whileNum)){
                    whileNum++;
                }
                black2white[e]=whileNum++;
            }
        }
    }
    
    int pick() {
        //随机数字ret MOD edge(即：从0-edge内随机返回白名单数字)：如果在black2white中则返回black2white[ret],
        //否则返回 ret
        int ret=rand()%edge;
        return black2white.count(ret)?black2white[ret]:ret;
    }
private:
    unordered_map<int,int> black2white;
    int edge;
};


//剑指 Offer 18. 删除链表的节点
/*
 *给定单向链表的头指针和一个要删除的节点的值，定义一个函数删除该节点。
返回删除后的链表的头节点。
 * */


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        if(head==nullptr){
            return head;
        }
        if(head->val==val){
            head=head->next;
            return head;
        }
        auto cur=head->next;
        auto pre=head;
        while(cur){
            if(cur->val==val){
                pre->next=cur->next;
                break;
            }else{
                pre=cur;
                cur=cur->next;
            }
        }
        return head;
    }
};
