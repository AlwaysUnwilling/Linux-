/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Sat 12 Feb 2022 10:33:27 PM CST
    > About:二叉树的后序遍历(非递归):给你一棵二叉树的根节点 root ，返回其节点值的 后序遍历 。
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
    vector<int> postorderTraversal(TreeNode* root) {
      vector<int> v;
      stack<TreeNode*> s;
      TreeNode* cur=root;
      TreeNode* lastNode=nullptr;  
      while(cur || !s.empty())
      {
          while(cur)
          {
            s.push(cur);
            cur=cur->left;
          }
          TreeNode* top=s.top();
          if(top->right==nullptr || lastNode==top->right)
          {
            v.push_back(top->val);
            lastNode=top; 
            s.pop();  
          }
          else  
          {
            cur=top->right;  
          }
      }
      return v;
    }
};

