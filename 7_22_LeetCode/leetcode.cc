#include<iostream>
#include<string>
#include<vector>

using namespace std;

//647. 回文子串
/*
 *给你一个字符串 s ，请你统计并返回这个字符串中 回文子串 的数目。

回文字符串 是正着读和倒过来读一样的字符串。

子字符串 是字符串中的由连续字符组成的一个序列。

具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串。
 * */

//暴力解法
class Solution {
public:
    bool isPalindrome(string& str)
    {
        int left=0;
        int right=str.size()-1;
        while(left<=right){
            if(str[left]!=str[right]){
                return false;
            }
            ++left;
            --right;
        }
        return true;
    }
    int countSubstrings(string s) {
        if(s.size() <= 1){
            return s.size();
        }
        int count=0;
        int len=s.size();
        for(int i=0;i < len;++i){
            for(int j=1;j <= len-i;++j){
                string tmp=s.substr(i,j);
                if(isPalindrome(tmp)){
                    count++;
                }
            }
        }
        return count;
    }
};

//617. 合并二叉树
/*
 *给你两棵二叉树： root1 和 root2 。

想象一下，当你将其中一棵覆盖到另一棵之上时，两棵树上的一些节点将会重叠（而另一些不会）。你需要将这两棵树合并成一棵新二叉树。合并的规则是：如果两个节点重叠，那么将这两个节点的值相加作为合并后节点的新值；否则，不为 null 的节点将直接作为新二叉树的节点。

返回合并后的二叉树。

注意: 合并过程必须从两个树的根节点开始。
 * */

//深度优先
 // Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if(root1==nullptr && root2==nullptr){
            return nullptr;
        }
        if(root1==nullptr){
            return root2;
        }else if(root2==nullptr){
            return root1;
        }else{
            TreeNode* root=new TreeNode(root1->val + root2->val);
            root->left=mergeTrees(root1->left,root2->left);
            root->right=mergeTrees(root1->right,root2->right);
            return root;
        }
    }
};

//广度优先：三个队列储存树的节点
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if(root1==nullptr){
            return root2;
        }
        if(root2==nullptr){
            return root1;
        }
        queue<TreeNode*> q,q1,q2;
        TreeNode* root=new TreeNode(root1->val + root2->val);
        q.push(root);
        q1.push(root1);
        q2.push(root2);
        while(!q1.empty() && !q2.empty()){
            auto front=q.front();
            auto front1=q1.front();
            auto front2=q2.front();
            q.pop();
            q1.pop();
            q2.pop();
            if(front1->left && front2->left){
                front->left=new TreeNode(front1->left->val + front2->left->val);
                q.push(front->left);
                q1.push(front1->left);
                q2.push(front2->left);
            }else if(front1->left){
                front->left=front1->left;
            }else if(front2->left){
                front->left=front2->left;
            }

            if(front1->right && front2->right){
                front->right=new TreeNode(front1->right->val + front2->right->val);
                q.push(front->right);
                q1.push(front1->right);
                q2.push(front2->right);
            }else if(front1->right){
                front->right=front1->right;
            }else if(front2->right){
                front->right=front2->right;
            }
        }
        return root;
    }
};
