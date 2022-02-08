/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Tue 08 Feb 2022 09:28:41 PM CST
    > About:二叉树的前序遍历(非递归)：给你二叉树的根节点 root ，返回它节点值的 前序 遍历。
 ************************************************************************/

#include<iostream>
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> v;
        if(root==nullptr){
            return v;
        }
        stack<TreeNode*> st;
        st.push(root);
        while(!st.empty()){
            TreeNode* top=st.top();
            st.pop();
            v.push_back(top->val);
            if(top->right){
                st.push(top->right);
            }
            if(top->left){
                st.push(top->left);
            }
        }
        return v;
    }
};

