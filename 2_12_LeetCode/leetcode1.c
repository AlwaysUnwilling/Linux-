/*************************************************************************
	> File Name: leetcode1.c
	> Author: 
	> Mail: 
	> Created Time: Sat 12 Feb 2022 10:36:27 PM CST
    > About:从中序与后序遍历序列构造二叉树:给定两个整数数组 inorder 和 postorder ，其中 inorder 是二叉树的中序遍历， postorder 是同一棵树的后序遍历，请你构造并返回这颗 二叉树 。

 

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
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
    TreeNode* _buildTree(vector<int>& inorder,vector<int>& postorder,int& postorderi,int left,int right)
    {
        if(le.ft>right)  return nullptr;
        TreeNode* root=new TreeNode(postorder[postorderi]);
        int rooti=right;
        for(rooti=right;rooti>=left;--rooti)
        {
            if(inorder[rooti]==postorder[postorderi])
            {
                break;
            }
        }
        //[left,rooti-1] rooti [rooti+1,right]
        if(rooti+1<=right)
        {
            root->right=_buildTree(inorder,postorder,--postorderi,rooti+1,right);
        }
        else
        {
            root->right=nullptr;
        }
        if(left<=rooti-1)
        {
            root->left=_buildTree(inorder,postorder,--postorderi,left,rooti-1);
        }
        else
        {
            root->left=nullptr;
        }
        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
      int postorderi=postorder.size()-1;
      int left=0,right=inorder.size()-1;
      return _buildTree(inorder, postorder,postorderi,left,right);
    }
};

