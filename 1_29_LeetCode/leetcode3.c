/*************************************************************************
	> File Name: leetcode3.c
	> Author: 
	> Mail: 
	> Created Time: Sat 29 Jan 2022 10:15:32 AM CST
    > About:另一棵树的子树:给你两棵二叉树 root 和 subRoot 。检验 root 中是否包含和 subRoot 具有相同结构和节点值的子树。如果存在，返回 true ；否则，返回 false 。

二叉树 tree 的一棵子树包括 tree 的某个节点和这个节点的所有后代节点。tree 也可以看做它自身的一棵子树。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/subtree-of-another-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
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

bool isSameTree(struct TreeNode* root,struct TreeNode* subRoot)
{
    if(root==NULL && subRoot==NULL){
        return true;
    }
    if(root==NULL && subRoot!=NULL){
        return false;
    }
    if(root!=NULL && subRoot==NULL){
        return false;
    }
    if(root->val==subRoot->val){
        return isSameTree(root->left,subRoot->left)
            && isSameTree(root->right,subRoot->right);
    }
    return false;
}
bool isSubtree(struct TreeNode* root, struct TreeNode* subRoot){
    if(root==NULL && subRoot==NULL){
        return true;
    }
    if(root==NULL && subRoot!=NULL){
        return false;
    }
    if(root!=NULL && subRoot==NULL){
        return false;
    }
    if(root->val==subRoot->val){
        if(isSameTree(root,subRoot)){
            return true;
        }else{
            return isSubtree(root->left,subRoot)
                || isSubtree(root->right,subRoot);
        }
    }else{
        return isSubtree(root->left,subRoot)
            || isSubtree(root->right,subRoot);
    }
}
