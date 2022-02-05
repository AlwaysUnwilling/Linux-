/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Sat 05 Feb 2022 10:15:53 PM CST
    > About:根据二叉树创建字符串:你需要采用前序遍历的方式，将一个二叉树转换成一个由括号和整数组成的字符串。

空节点则用一对空括号 "()" 表示。而且你需要省略所有不影响字符串与原始二叉树之间的一对一映射关系的空括号对。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/construct-string-from-binary-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<iostream>
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void _tree2str(TreeNode* root,string& str)
    {
        if(root==nullptr){
            return ;
        }
        str+=to_string(root->val);
       
        if(root->left==nullptr && root->right){
            str+="()(";
            _tree2str(root->right,str);
            str+=')';
        }else if(root->left && root->right){
            str+='(';
            _tree2str(root->left,str);
            str+=')';
            str+='(';
            _tree2str(root->right,str);
            str+=')';
        }else if(root->left && root->right==nullptr){
            str+='(';
            _tree2str(root->left,str);
            str+=')';
        }else{
            ;
        }
    }
    string tree2str(TreeNode* root) {
        string str;
        _tree2str(root,str);
        return str;
    }
};
