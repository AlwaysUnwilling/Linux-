/*************************************************************************
	> File Name: leetcode1.c
	> Author: 
	> Mail: 
	> Created Time: Tue 08 Feb 2022 10:19:07 PM CST
    > About:二叉树的中序遍历(非递归)：给定一个二叉树的根节点 root ，返回它的 中序 遍历。
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
    vector<int> inorderTraversal(TreeNode* root) {
      vector<int> v;
      stack<TreeNode*> s;
      TreeNode* cur=root;
      while(cur || !s.empty())
      {
          while(cur)
          {
              s.push(cur);
              cur=cur->left;
          }
          TreeNode* top=s.top();
          s.pop();
          v.push_back(top->val);
          cur=top->right;
      }
      return v;
    }
};

