#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//406. 根据身高重建队列
/*
 *假设有打乱顺序的一群人站成一个队列，数组 people 表示队列中一些人的属性（不一定按顺序）。每个 people[i] = [hi, ki] 表示第 i 个人的身高为 hi ，前面 正好 有 ki 个身高大于或等于 hi 的人。

请你重新构造并返回输入数组 people 所表示的队列。返回的队列应该格式化为数组 queue ，其中 queue[j] = [hj, kj] 是队列中第 j 个人的属性（queue[0] 是排在队列前面的人）。
 * */

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        if(people.size()==1){
            return people;
        }
        sort(people.begin(),people.end(),[](vector<int>& p1,vector<int>& p2){
            return p1[0] < p2[0] || (p1[0]==p2[0] && p1[1] > p2[1]);
        });
        vector<vector<int>> queue(people.size());
        for(const auto& p:people){
            int index=p[1]+1;
            for(int i=0;i < (int)people.size();++i){
                if(queue[i].empty()){
                    index--;
                    if(index==0){
                        queue[i]=p;
                        break;
                    }
                }
            }
        }
        return queue;
    }
};

//538. 把二叉搜索树转换为累加树
/*
 *给出二叉 搜索 树的根节点，该树的节点值各不相同，请你将其转换为累加树（Greater Sum Tree），使每个节点 node 的新值等于原树中大于或等于 node.val 的值之和。

提醒一下，二叉搜索树满足下列约束条件：

节点的左子树仅包含键 小于 节点键的节点。
节点的右子树仅包含键 大于 节点键的节点。
左右子树也必须是二叉搜索树。
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
    void _convertBST(TreeNode* root,int& sum)
    {
        if(root==nullptr){
            return ;
        }else{
            _convertBST(root->right,sum);
            sum+=root->val;
            root->val=sum;
            _convertBST(root->left,sum);
        }
    }
    TreeNode* convertBST(TreeNode* root) {
        int sum=0;
        _convertBST(root,sum);
        return root;
    }
};
