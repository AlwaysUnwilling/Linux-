#include<iostream>
#include<vector>
#include<stack>

using namespace std;

//450. 删除二叉搜索树中的节点
/*
 *给定一个二叉搜索树的根节点 root 和一个值 key，删除二叉搜索树中的 key 对应的节点，并保证二叉搜索树的性质不变。返回二叉搜索树（有可能被更新）的根节点的引用。

一般来说，删除节点可分为两个步骤：

首先找到需要删除的节点；
如果找到了，删除它。
 * */


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root==nullptr){
            return root;
        }
        TreeNode* cur=root;
        TreeNode* parent=nullptr;
        while(cur){
            if(cur->val==key){
                break;
            }else if(cur->val>key){
                parent=cur;
                cur=cur->left;
            }else{
                parent=cur;
                cur=cur->right;
            }
        }
        if(cur==nullptr){
            return root;
        }
        //根节点val==key
        if(parent==nullptr){
            if(root->left==nullptr && root->right==nullptr){
                delete root;
                return nullptr;
            }else if(root->left && root->right==nullptr){
                TreeNode* newRoot=root->left;
                delete root;
                root=newRoot;
                return root;
            }else if(root->left==nullptr && root->right){
                TreeNode* newRoot=root->right;
                delete root;
                root=newRoot;
                return root;
            }else{
                TreeNode* newNode=root->right;
                TreeNode* rParent=root;
                while(newNode->left){
                    rParent=newNode;
                    newNode=newNode->left;
                }
                if(rParent==root){
                    newNode->left=root->left;
                }else{
                    newNode->left=root->left;
                    newNode->right=root->right;
                    rParent->left=nullptr;
                }
                delete root;
                root=newNode;
                return root;                
            }
        }
        //根节点不是key
        if(cur->left==nullptr && cur->right==nullptr){
            if(parent->left==cur){
                parent->left=nullptr;
            }else{
                parent->right=nullptr;
            }
            delete cur;
            return root;
        }else if(cur->left && cur->right==nullptr){
            if(parent->left==cur){
                parent->left=cur->left;
            }else{
                parent->right=cur->left;
            }
            delete cur; 
            return root; 
        }else if(cur->left==nullptr && cur->right){
            if(parent->left==cur){
                parent->left=cur->right;
            }else{
                parent->right=cur->right;
            }
            delete cur;
            return root;
        }else{
            TreeNode* newNode=cur->right;
            TreeNode* cParent=cur;
            while(newNode->left){
                cParent=newNode;
                newNode=newNode->left;
            }
            newNode->left=cur->left;
            TreeNode* newRight=newNode->right;
            if(newNode!=cur->right){
                newNode->right=cur->right;
                cParent->left=newRight;
            }
                       
            if(parent->left==cur){
                parent->left=newNode;
            }else{
                parent->right=newNode;
            }
            delete cur;
            return root;
        }
    }
};

//剑指 Offer 31. 栈的压入、弹出序列
/*
 * 输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如，序列 {1,2,3,4,5} 是某栈的压栈序列，序列 {4,5,3,2,1} 是该压栈序列对应的一个弹出序列，但 {4,3,5,1,2} 就不可能是该压栈序列的弹出序列。
 * */

class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        if(pushed.size()!=popped.size()){
            return false;
        }
        stack<int> st;
        int index=0;
        int size=pushed.size();
        for(int i=0;i<size;++i){
            st.push(pushed[i]);
            while(index<size && !st.empty() && st.top()==popped[index]){
                st.pop();
                index++;
            }
        }
        return st.empty();
    }
};
