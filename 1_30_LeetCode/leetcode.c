/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Sun 30 Jan 2022 10:32:35 AM CST
    > About:平衡二叉树:给定一个二叉树，判断它是否是高度平衡的二叉树。

本题中，一棵高度平衡二叉树定义为：

一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1 。
 ************************************************************************/

#include<stdio.h>
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int treeDepth(struct TreeNode* root)
{
    if(root==NULL){
        return 0;
    }
    int leftDepth=treeDepth(root->left);
    int rightDepth=treeDepth(root->right);
    return leftDepth>rightDepth?leftDepth+1:rightDepth+1;
}
bool isBalanced(struct TreeNode* root){
    if(root==NULL){
        return true;
    }
    int leftDepth=treeDepth(root->left);
    int rightDepth=treeDepth(root->right);
    if(abs(leftDepth-rightDepth)>1){
        return false;
    }else{
        return isBalanced(root->left)
            && isBalanced(root->right);
    }
}
