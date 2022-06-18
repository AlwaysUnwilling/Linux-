#include<iostream>
#include<unordered_map>

using namespace std;

//剑指 Offer II 029. 排序的循环链表
/*
 *给定循环单调非递减列表中的一个点，写一个函数向这个列表中插入一个新元素 insertVal ，使这个列表仍然是循环升序的。

给定的可以是这个列表中任意一个顶点的指针，并不一定是这个列表中最小元素的指针。

如果有多个满足条件的插入位置，可以选择任意一个位置插入新的值，插入后整个列表仍然保持有序。

如果列表为空（给定的节点是 null），需要创建一个循环有序列表并返回这个节点。否则。请返回原先给定的节点。
 * */


// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};


class Solution {
public:
    void _insert(Node* cur,Node* pre,int insertVal,unordered_map<Node*,int>& visited)
    {
        if(insertVal==cur->val){
            cur->next=new Node(insertVal,cur->next);
        }else if(insertVal>cur->val){
            while(cur->val<insertVal && !visited[cur] && cur->val<=cur->next->val){
                visited[cur]=true;
                pre=cur;
                cur=cur->next;
            } 
            if(cur->val>=insertVal){
                pre->next=new Node(insertVal,pre->next);
            }else{
                cur->next=new Node(insertVal,cur->next);
            }
        }else{
            while(cur->val<=cur->next->val && !visited[cur]){
                visited[cur]=true;
                pre=cur;
                cur=cur->next;
            }
            //只有当cur->val<=cur->next->val不满足时才会推出循环
            if(cur->next->val>=insertVal){
                cur->next=new Node(insertVal,cur->next);
            }else{
                visited[cur]=true;
                pre=cur;
                cur=cur->next;
                _insert(cur,pre,insertVal,visited);
            }
        }
    }
    Node* insert(Node* head, int insertVal) {
        if(head==nullptr){
            head=new Node(insertVal);
            head->next=head;
            return head;
        }
        if(head->next==head){
            head->next=new Node(insertVal,head->next);
            return head;
        }
        unordered_map<Node*,int> visited;
        Node* cur=head;
        Node* pre=nullptr;
        _insert(cur,pre,insertVal,visited);
        return head;
    }
};

//剑指 Offer 48. 最长不含重复字符的子字符串
/*
 *请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子字符串的长度。
 * */

//动态规化： //动态规划vector<int> dp(n+1);表示字符串s第i个位置的不重复子字符串的长度，tmp表示此时的不重复的字符串
    //dp[1+i]:如果s[i]能在tmp中找到，则dp[i+1]就等于从tmp重复字符后开始的长度+1(s[i]的长度)；否则
    //dp[i+1]=dp[i]+1;
  
class Solution {
public:
    //动态规划vector<int> dp(n+1);表示字符串s第i个位置的不重复子字符串的长度，tmp表示此时的不重复的字符串
    //dp[1+i]:如果s[i]能在tmp中找到，则dp[i+1]就等于从tmp重复字符后开始的长度+1(s[i]的长度)；否则
    //dp[i+1]=dp[i]+1;
    int lengthOfLongestSubstring(string s) {
        if(s.size()==0 ||s.size()==1){
            return s.size();
        }
        int n=s.size();
        vector<int> dp(n+1);
        dp[1]=1;
        string tmp;
        tmp+=s[0];
        for(int i=1;i<n;++i){
            size_t index=tmp.find(s[i]);
            if(index==string::npos){
                tmp+=s[i];
                dp[i+1]=dp[i]+1;
            }else{
                tmp=tmp.substr(index+1);
                tmp+=s[i];
                dp[i+1]=tmp.size();
            }
        }
        int maxLength=0;
        for(const auto& e:dp){
            if(e>maxLength){
                maxLength=e;
            }
        }
        return maxLength;
    }
};
