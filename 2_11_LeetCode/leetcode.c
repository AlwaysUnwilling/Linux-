/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Fri 11 Feb 2022 10:34:18 PM CST
    > About:从前序与中序遍历序列构造二叉树:给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal
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
    TreeNode* _buildTree(vector<int>& preorder, vector<int>& inorder,int& prei,int inbegin,int inend)
    {
        if(inbegin>inend)   
        return nullptr;
        TreeNode* root=new TreeNode(preorder[prei]);
        int rooti=inbegin;
        while(rooti<=inend)
        {
            if(inorder[rooti]==preorder[prei])
            break;
            else
            ++rooti;
        }
        if(inbegin<=rooti-1)  
        root->left=_buildTree(preorder,inorder,++prei,inbegin,rooti-1);
        else
        root->left=nullptr;
        if(rooti+1<=inend)   
        root->right=_buildTree(preorder,inorder,++prei,rooti+1,inend);
        else
        root->right=nullptr;
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
      int prei=0,inbegin=0,inend=inorder.size()-1;
      return _buildTree(preorder,inorder,prei,inbegin,inend);
    }
};


