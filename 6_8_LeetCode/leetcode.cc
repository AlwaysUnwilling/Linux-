#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

//剑指 Offer 38. 字符串的排列
/*
 *输入一个字符串，打印出该字符串中字符的所有排列。
你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。
 * */

class Solution {
public:
    void GetSort(const string& s,int i,int n,string& tmp,vector<string>& res,vector<bool>& vis)
    {
        if(i==n){
            res.push_back(tmp);
            return ;
        }
        for(int j=0;j<n;++j){
            if(vis[j] || (j>0 && !vis[j - 1] && s[j-1]==s[j])){
                continue;
            }
            vis[j]=true;
            tmp+=s[j];
            GetSort(s,i+1,n,tmp,res,vis);
            tmp.pop_back();
            vis[j]=false;
        }
    }
    vector<string> permutation(string s) {
        vector<string> res;
        if(s.size()==0){
            return res;
        }
        if(s.size()==1){
            res.push_back(s);
            return res;
        }
        int n=s.size();
        string tmp;
        sort(s.begin(),s.end());
        vector<bool> vis(n,false);
        GetSort(s,0,n,tmp,res,vis);
        return res;
    }
};

//剑指 Offer 28. 对称的二叉树
/*
 *请实现一个函数，用来判断一棵二叉树是不是对称的。如果一棵二叉树和它的镜像一样，那么它是对称的。
 * */


//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isSameTree(TreeNode* root1,TreeNode* root2)
    {
        if((root1==nullptr && root2) || (root1 && root2==nullptr)){
            return false;
        }
        if(root1==nullptr && root2==nullptr){
            return true;
        }
        if(root1->val!=root2->val){
            return false;
        }
        return isSameTree(root1->left,root2->right)
            && isSameTree(root1->right,root2->left);
    }
    bool isSymmetric(TreeNode* root) {
        if(root==nullptr){
            return true;
        }
        return isSameTree(root->left,root->right);
    }
};

