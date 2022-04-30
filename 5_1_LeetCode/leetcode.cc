#include<iostream>
#include<vector>

using namespace std;

//1305. 两棵二叉搜索树中的所有元素
/*
 *给你 root1 和 root2 这两棵二叉搜索树。请你返回一个列表，其中包含 两棵树 中的所有整数并按 升序 排序。.
 * */

/**
 * Definition for a binary tree node.*/
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
    void _getAllElements(TreeNode* root,vector<int>& v)
    {
        if(root==nullptr) return;
        _getAllElements(root->left,v);
        v.push_back(root->val);
        _getAllElements(root->right,v);
    }
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        vector<int> ret;
        vector<int> v1;
        vector<int> v2;
        _getAllElements(root1,v1);
        _getAllElements(root2,v2);
        int end1=0;
        int end2=0;
        while(end1<v1.size() && end2<v2.size()){
            if(v1[end1]<v2[end2]){
                ret.push_back(v1[end1++]);
            }else{
                ret.push_back(v2[end2++]);
            }
        }
        while(end1<v1.size()){
            ret.push_back(v1[end1++]);
        }
        while(end2<v2.size()){
            ret.push_back(v2[end2++]);
        }
        return ret;
    }
};

//337. 打家劫舍 III
/*
 *小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为 root 。

除了 root 之外，每栋房子有且只有一个“父“房子与之相连。一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。 如果 两个直接相连的房子在同一天晚上被打劫 ，房屋将自动报警。

给定二叉树的 root 。返回 在不触动警报的情况下 ，小偷能够盗取的最高金额 。
 * */

/**
 Definition for a binary tree node.*/ 
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
    std::pair<int,int> _dfs(TreeNode* root)
    {
        if(root==nullptr) return {0,0};
        auto _left=_dfs(root->left);
        auto _right=_dfs(root->right);
        int stolen=root->val+_left.second+_right.second;
        int notstolen=max(_left.first,_left.second)+max(_right.first,_right.second);
        return {stolen,notstolen};
    }
    int rob(TreeNode* root) {
        //动态规划：对于每个节点都存在被选中(F(root))和不被选中(G(root))俩种状态，那么当小偷到达第i个节点时，
        //若该节点被选中F(root)，那么财富F(root)=root->val+G(root->left)+G(root->right);
        //若该节点不被选中G(root)，那么财富G(root)=max(F(root->left),G(root->left))+max(F(root->right),G(root->right));
        //结果：小偷行窃地区的入口小屋(树的根节点)被偷和不被偷中小偷获取的最大财富值中较大者。
        //maxWealth=max(F(root),G(root));
        //std::pair<int,int> ret;       //ret.first--被偷；ret.second--不被偷
        auto ret=_dfs(root);   //后续遍历
        return max(ret.first,ret.second);
    }
};
