#include<iostream>
#include<queue>
#include<vector>
#include<unordered_set>


using namespace std;

//513. 找树左下角的值
/*
 *给定一个二叉树的 根节点 root，请找出该二叉树的 最底层 最左边 节点的值。

假设二叉树中至少有一个节点。
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
    int findBottomLeftValue(TreeNode* root) {
        if(root->left==nullptr && root->right==nullptr){
            return root->val;
        }
        queue<TreeNode*> q;
        q.push(root);
        vector<vector<TreeNode*>> vv;
        while(!q.empty()){
            int n=q.size();
            vector<TreeNode*> v;
            for(int i=0;i<n;++i){
                auto node=q.front();
                q.pop();
                if(node->left){
                    q.push(node->left);
                    v.push_back(node->left);
                }
                if(node->right){
                    q.push(node->right);
                    v.push_back(node->right);
                }
            }
            if(v.size()){
                vv.push_back(v);
            }
        }
        int m=vv.size();
        return vv[m-1][0]->val;
    }
};

//剑指 Offer 49. 丑数
/*
 *我们把只包含质因子 2、3 和 5 的数称作丑数（Ugly Number）。求按从小到大的顺序的第 n 个丑数。
 * */

class Solution {
public:
    int nthUglyNumber(int n) {
        //如果i是丑数，那么2*i，3*i，5*i也是丑数
        //1是丑数，把1先入（小堆）堆，然后取出堆顶的最小数，堆他依次乘以2、3、5，再次入堆
        //由于可能会有重复的数字进入堆，因此入堆前先去重。
        priority_queue<long long,vector<long long>,greater<long long>> pq;
        unordered_set<long long> st;
        vector<int> factor{2,3,5};
        pq.push(1);
        st.insert(1);
        long long cur=0;
        while(n--){
            cur=pq.top();
            pq.pop();
            long long next=cur;
            for(auto& e:factor){
                next=e*cur;
                if(st.count(next)==0){
                    pq.push(next);
                    st.insert(next);
                }
            }
        }
        return (int)cur;
    }
};
