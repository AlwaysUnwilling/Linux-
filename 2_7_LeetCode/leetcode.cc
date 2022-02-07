/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Mon 07 Feb 2022 09:59:23 PM CST
    > About: 二叉树的最近公共祖先:给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<iostream>
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool IsInTheTree(TreeNode* root,TreeNode* sub)
    {
        if(root==nullptr){
            return false;
        }
        if(root==sub){
            return true;
        }
        return IsInTheTree(root->left,sub)
            || IsInTheTree(root->right,sub);
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root==nullptr){
            return nullptr;
        } 
        if(root==p || root==q){
            return root;
        }
        if(IsInTheTree(root->left,p)){
            if(IsInTheTree(root->right,q)){
                return root;
            }else{
                return lowestCommonAncestor(root->left,p,q);
            }
        }else{
            if(IsInTheTree(root->left,q)){
                return root;
            }else{
                return lowestCommonAncestor(root->right,p,q);
            }
        }
    }
};
