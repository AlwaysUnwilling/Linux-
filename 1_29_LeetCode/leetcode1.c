/*************************************************************************
	> File Name: leetcode1.c
	> Author: 
	> Mail: 
	> Created Time: Sat 29 Jan 2022 09:48:53 AM CST
    > About:二叉树的中序遍历:给定一个二叉树的根节点 root ，返回它的 中序 遍历。
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
void _inorderTraversal(struct TreeNode* root,int* i,int**arr)
{
    if(root==NULL){
        return ;
    }
    _inorderTraversal(root->left,i,arr);
    (*arr)[*i]=root->val;
    (*i)++;
    _inorderTraversal(root->right,i,arr);
} 
int* inorderTraversal(struct TreeNode* root, int* returnSize){
    if(root==NULL){
        *returnSize=0;      
        return NULL;
    }
    int* array=(int*)malloc(sizeof(int)*100);
    int index=0;
    _inorderTraversal(root,&index,&array);
    *returnSize=index;
    return array;
}
