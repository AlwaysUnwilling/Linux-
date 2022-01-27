/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Thu 27 Jan 2022 10:44:36 AM CST
    > About:单值二叉树:如果二叉树每个节点都具有相同的值，那么该二叉树就是单值二叉树。

只有给定的树是单值二叉树时，才返回 true；否则返回 false。
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

bool _isUnivalTree(struct TreeNode* root,int num)
{
    if(root==NULL){
        return true;
    }
    if(root->val==num){
        return _isUnivalTree(root->left,num)
            && _isUnivalTree(root->right,num);
    }
    return false;
}
bool isUnivalTree(struct TreeNode* root){
    if(root==NULL){
        return true;
    }
    int num=root->val;
    return _isUnivalTree(root->left,num)
        && _isUnivalTree(root->right,num);
}
