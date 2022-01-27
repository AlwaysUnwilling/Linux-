/*************************************************************************
	> File Name: leetcode2.c
	> Author: 
	> Mail: 
	> Created Time: Thu 27 Jan 2022 11:02:10 AM CST
    > About:翻转二叉树:给你一棵二叉树的根节点 root ，翻转这棵二叉树，并返回其根节点。
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


struct TreeNode* invertTree(struct TreeNode* root){
    if(root==NULL){
        return NULL;
    }
    struct TreeNode* _left=root->left;
    root->left=invertTree(root->right);
    root->right=invertTree(_left);
    return root;
}
