/*************************************************************************
	> File Name: leetcode2.c
	> Author: 
	> Mail: 
	> Created Time: Sat 29 Jan 2022 09:51:09 AM CST
    > About:二叉树的后序遍历:给你一棵二叉树的根节点 root ，返回其节点值的 后序遍历 。
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


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
void _postorderTraversal(struct TreeNode* root,int* i,int**arr)
{
    if(root==NULL){
        return ;
    }
    _postorderTraversal(root->left,i,arr);
    _postorderTraversal(root->right,i,arr);
    (*arr)[*i]=root->val;
    (*i)++;
}
int* postorderTraversal(struct TreeNode* root, int* returnSize){
    if(root==NULL){
        *returnSize=0;      
        return NULL;
    }
    int* array=(int*)malloc(sizeof(int)*100);
    int index=0;
    _postorderTraversal(root,&index,&array);
    *returnSize=index;
    return array;
}
