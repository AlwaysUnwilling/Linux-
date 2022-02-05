/*************************************************************************
	> File Name: leetcode2.c
	> Author: 
	> Mail: 
	> Created Time: Sat 05 Feb 2022 10:53:45 PM CST
    > About:二叉树的层序遍历 II:给你二叉树的根节点 root ，返回其节点值 自底向上的层序遍历 。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）
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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> vv;
        if(root==nullptr){
            return vv;
        }
        queue<TreeNode*> q1;
        queue<TreeNode*> q2;
        q1.push(root);
        while(!q1.empty() || !q2.empty()){
            vector<int> v;
            if(!q2.empty()){
                while(!q2.empty()){
                    TreeNode* front=q2.front();
                    q2.pop();
                    if(front->left){
                        q1.push(front->left);
                    }
                    if(front->right){
                        q1.push(front->right);
                    }
                    v.push_back(front->val);
                }
            }else{
                while(!q1.empty()){
                    TreeNode* front=q1.front();
                    q1.pop();
                    if(front->left){
                        q2.push(front->left);
                    }
                    if(front->right){
                        q2.push(front->right);
                    }
                    v.push_back(front->val);
                }
            }
            vv.push_back(v);
        }
        reverse(vv.begin(),vv.end());
        return vv;
    }
};

