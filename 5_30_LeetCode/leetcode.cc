#include<iostream>
#include<vector>


using namespace std;

//1022. 从根到叶的二进制数之和
/*
 *给出一棵二叉树，其上每个结点的值都是 0 或 1 。每一条从根到叶的路径都代表一个从最高有效位开始的二进制数。

例如，如果路径为 0 -> 1 -> 1 -> 0 -> 1，那么它表示二进制数 01101，也就是 13 。
对树上的每一片叶子，我们都要找出从根到该叶子的路径所表示的数字。

返回这些数字之和。题目数据保证答案是一个 32 位 整数。
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
    int PostOrder(TreeNode* root,int ret)
    {
        if(root==nullptr){
            return 0;
        }
        ret=(ret<<1)|root->val;
        if(root->left==nullptr && root->right==nullptr){
            return ret;
        }
        return PostOrder(root->left,ret)+PostOrder(root->right,ret);
    }
    int sumRootToLeaf(TreeNode* root) {
        if(root==nullptr){
            return 0;
        }
        return PostOrder(root,0);
    }
};


//剑指 Offer 11. 旋转数组的最小数字
/*
 *把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。

给你一个可能存在 重复 元素值的数组 numbers ，它原来是一个升序排列的数组，并按上述情形进行了一次旋转。请返回旋转数组的最小元素。例如，数组 [3,4,5,1,2] 为 [1,2,3,4,5] 的一次旋转，该数组的最小值为 1。  
 * */


class Solution {
public:
    int minArray(vector<int>& numbers) {
        int left=0;
        int right=numbers.size()-1;
        while(left<right){
            int mid=(left+right)>>1;
            if(numbers[mid]>numbers[right]){
                left=mid+1;
            }else if(numbers[mid]<numbers[left]){
                right=mid;
            }else{
                right--;
            }
        }
        return numbers[left];
    }
};
