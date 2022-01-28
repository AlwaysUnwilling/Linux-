/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Fri 28 Jan 2022 11:35:00 AM CST
    > About:相同的树:给你两棵二叉树的根节点 p 和 q ，编写一个函数来检验这两棵树是否相同。

如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。
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
