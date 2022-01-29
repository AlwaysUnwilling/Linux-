/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Sat 29 Jan 2022 09:46:15 AM CST
    > About:二叉树的前序遍历:给你二叉树的根节点 root ，返回它节点值的 前序 遍历。
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
void _preorderTraversal(struct TreeNode* root,int* i,int**arr)
{
    if(root==NULL){
        return ;
    }
    (*arr)[*i]=root->val;
    (*i)++;
    _preorderTraversal(root->left,i,arr);
    _preorderTraversal(root->right,i,arr);
} 
int* preorderTraversal(struct TreeNode* root, int* returnSize){
    if(root==NULL){
        *returnSize=0;      
        return NULL;
    }
    int* array=(int*)malloc(sizeof(int)*100);
    int index=0;
    _preorderTraversal(root,&index,&array);
    *returnSize=index;
    return array;
}
