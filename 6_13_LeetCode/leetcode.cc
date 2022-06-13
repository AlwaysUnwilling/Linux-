#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//1051. 高度检查器
/*
 *学校打算为全体学生拍一张年度纪念照。根据要求，学生需要按照 非递减 的高度顺序排成一行。

排序后的高度情况用整数数组 expected 表示，其中 expected[i] 是预计排在这一行中第 i 位的学生的高度（下标从 0 开始）。

给你一个整数数组 heights ，表示 当前学生站位 的高度情况。heights[i] 是这一行中第 i 位学生的高度（下标从 0 开始）。

返回满足 heights[i] != expected[i] 的 下标数量 。
 * */

//快排
class Solution {
public:
    int heightChecker(vector<int>& heights) {
        if(heights.size()==0 || heights.size()==1){
            return 0;
        }
        auto expected=heights;
        sort(expected.begin(),expected.end());
        int count=0;
        for(int i=0;i<heights.size();++i){
            if(heights[i]!=expected[i]){
                count++;
            }
        }
        return count;
    }
};

//计数排序
class Solution {
public:
    int heightChecker(vector<int>& heights) {
        if(heights.size()==0 || heights.size()==1){
            return 0;
        }
        int maxValue=INT_MIN;
        for(const auto& e:heights){
            maxValue=max(e,maxValue);
        }
        vector<int> count(maxValue+1);
        for(const auto& e:heights){
            count[e]++;
        }
        int index=0,res=0;
        for(int i=1;i<=maxValue;++i){
            for(int j=1;j<=count[i];++j){
                if(heights[index]!=i){
                    res++;
                }
                index++;
            }
        }
        return res;
    }
};

//剑指 Offer 34. 二叉树中和为某一值的路径
/*
 *给你二叉树的根节点 root 和一个整数目标和 targetSum ，找出所有 从根节点到叶子节点 路径总和等于给定目标和的路径。

叶子节点 是指没有子节点的节点。
 * */


//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//dfs
class Solution {
public:
    void _pathSum(TreeNode* root,vector<vector<int>>& vv,vector<int>& v,int sum,int target)
    {
        if(root==nullptr){
            return ;
        }
        sum+=root->val;
        //cout<<"sum:"<<sum<<endl;
        v.push_back(root->val);
        if(root->left==nullptr && root->right==nullptr){
            if(sum==target){
                vv.push_back(v);
            }
            v.pop_back();
            return ;
        }
        _pathSum(root->left,vv,v,sum,target);
        _pathSum(root->right,vv,v,sum,target);
        v.pop_back();
    }
    vector<vector<int>> pathSum(TreeNode* root, int target) {
        if(root==nullptr){
            return {};
        }
        vector<vector<int>> vv;
        vector<int> v;
        int sum=0;
        _pathSum(root,vv,v,sum,target);
        return vv;
    }
};

//广度遍历

#include<unordered_map>
#include<algorithm>

class Solution {
public:
    void GetPathVal(TreeNode* node)
    {
        vector<int> v;
        while(node){
            v.push_back(node->val);
            node=PCmap[node];
        }
        reverse(v.begin(),v.end());
        vv.push_back(v);
    }
    vector<vector<int>> pathSum(TreeNode* root, int target) {
        if(root==nullptr){
            return {};
        }
        queue<TreeNode*> q;
        queue<int> sum_q;
        q.push(root);
        sum_q.push(0);
        while(!q.empty()){
            TreeNode* node=q.front();
            q.pop();
            int sum=sum_q.front()+node->val;
            sum_q.pop();
            if(node->left==nullptr && node->right==nullptr){
                //叶子节点
                if(sum==target){
                    GetPathVal(node);
                }
            }else{
                //sum-=node->val;
                if(node->left){
                    q.push(node->left);
                    //记录node->left的父节点
                    PCmap[node->left]=node; 
                    sum_q.push(sum); 
                }
                if(node->right){
                    q.push(node->right);
                    //记录node->right的父节点
                    PCmap[node->right]=node;
                    sum_q.push(sum);
                }
            }
        }
        return vv;
    }
private:
    unordered_map<TreeNode*,TreeNode*> PCmap;
    vector<vector<int>> vv;
};
