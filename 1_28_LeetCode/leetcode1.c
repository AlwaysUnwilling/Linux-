/*************************************************************************
	> File Name: leetcode1.c
	> Author: 
	> Mail: 
	> Created Time: Fri 28 Jan 2022 11:54:36 AM CST
    > About:对称二叉树:给你一个二叉树的根节点 root ， 检查它是否轴对称。
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

bool isSameTree(struct TreeNode* p, struct TreeNode* q){
    if(p==NULL && q!=NULL){
        return false;
    }
    if(p!=NULL && q==NULL){
        return false;
    }
    if(p==NULL && q==NULL){
        return true;
    }
    if(p->val==q->val){
        return isSameTree(p->left,q->left)
            && isSameTree(p->right,q->right);
    }
    return false;
}
struct TreeNode* turnTree(struct TreeNode* root)
{
    if(root==NULL){
        return NULL;
    }
    struct TreeNode* Left=root->left;
    root->left=turnTree(root->right);
    root->right=turnTree(Left);
    return root;
}
bool isSymmetric(struct TreeNode* root){
    if(root==NULL){
        return true;
    }
    root->left=turnTree(root->left);
    return isSameTree(root->left,root->right);
}
