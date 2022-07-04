#include<iostream>
#include<vector>
#include<queue>

using namespace std;

//BM7 链表中环的入口结点
/*
 *描述
给一个长度为n链表，若其中包含环，请找出该链表的环的入口结点，否则，返回null。
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
    ListNode* EntryNodeOfLoop(ListNode* pHead) {
        if(pHead==nullptr || pHead->next==nullptr){
            return nullptr;
        }
        auto fast=pHead;
        auto slow=pHead;
        while(fast && fast->next){
            slow=slow->next;
            fast=fast->next->next;
            if(fast==slow){
                break;
            }
        }
        if(fast==nullptr || fast->next==nullptr){
            return nullptr;
        }
        fast=pHead;
        while(fast!=slow){
            fast=fast->next;
            slow=slow->next;
        }
        return fast;
    }
};

//BM41 输出二叉树的右视图
/*
 *描述
请根据二叉树的前序遍历，中序遍历恢复二叉树，并打印出二叉树的右视图

数据范围： 0 \le n \le 100000≤n≤10000
要求： 空间复杂度 O(n)O(n)，时间复杂度 O(n)O(n)
 * */

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 求二叉树的右视图
     * @param xianxu int整型vector 先序遍历
     * @param zhongxu int整型vector 中序遍历
     * @return int整型vector
     */
    vector<int> ret;
    void Inorder(TreeNode* root)
    {
        if(root==nullptr){
            return ;
        }
        Inorder(root->left);
        cout<<root->val<<endl;
        Inorder(root->right);
    }
    TreeNode* rebuildTree(vector<int>& xianxu,vector<int>& zhongxu,int& index,int left,int right)
    {
        if(index>=xianxu.size()){
            return nullptr;
        }
        if(left>right){
            return nullptr;
        }
        
        int rooti=0;
        TreeNode* root=new TreeNode(xianxu[index]);
        for(int i=left;i<=right;++i){
            if(zhongxu[i]==xianxu[index]){
                rooti=i;
                break;
            }
        }
        ++index;
        root->left=rebuildTree(xianxu,zhongxu,index,left,rooti-1);
        root->right=rebuildTree(xianxu,zhongxu,index,rooti+1,right);
        return root;
    }
    vector<int> solve(vector<int>& xianxu, vector<int>& zhongxu) {
        if(xianxu.size()==0 || zhongxu.size()==0){
            return {};
        }
        int n=xianxu.size();
        int index=0;
        TreeNode* root=rebuildTree(xianxu,zhongxu,index,0,n-1);
        Inorder(root);
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int size=q.size();
            for(int i=0;i<size;++i){
                auto front=q.front();
                q.pop();
                if(i==size-1){
                    ret.push_back(front->val);
                }
                if(front->left){
                    q.push(front->left);
                }
                if(front->right){
                    q.push(front->right);
                }
            }
        }
        return ret;
    }
};
