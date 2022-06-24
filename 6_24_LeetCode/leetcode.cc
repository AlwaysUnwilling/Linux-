#include<iostream>
#include<vector>
#include<queue>
#include<limits.h>

using namespace std;

//515. 在每个树行中找最大值
/*
 *给定一棵二叉树的根节点 root ，请找出该二叉树中每一层的最大值。
 * */

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
    vector<int> largestValues(TreeNode* root) {
        if(root==nullptr){
            return {};
        }
        vector<int> maxVal;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int n=q.size();
            int num=INT_MIN;
            for(int i=0;i<n;++i){
                auto node=q.front();
                q.pop();
                num=max(num,node->val);
                if(node->left){
                    q.push(node->left);
                }
                if(node->right){
                    q.push(node->right);
                }
            }
            maxVal.push_back(num);
        }
        return maxVal;
    }
};


//剑指 Offer 57. 和为s的两个数字
/*
 *输入一个递增排序的数组和一个数字s，在数组中查找两个数，使得它们的和正好是s。如果有多对数字的和等于s，则输出任意一对即可。
 * */

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        if(nums.size()<2 || target<nums[0]){
            return {};
        }
        int n=nums.size();
        int left=0,right=n-1;
        while(left<right){
            if(nums[left]+nums[right]>target){
                right--;
            }else if(nums[left]+nums[right]<target){
                left++;
            }else{
                return {nums[left],nums[right]};
            }
        }
        return {};
    }
};
