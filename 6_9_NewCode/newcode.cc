#include<iostream>
#include<queue>

using namespace std;

//BM35 判断是不是完全二叉树
/*
 *给定一个二叉树，确定他是否是一个完全二叉树。
完全二叉树的定义：若二叉树的深度为 h，除第 h 层外，其它各层的结点数都达到最大个数，第 h 层所有的叶子结点都连续集中在最左边，这就是完全二叉树。（第 h 层可能包含 [1~2h] 个节点）
数据范围：节点数满足 1 \le n \le 100 \1≤n≤100 
 * */


struct TreeNode {
  int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param root TreeNode类 
     * @return bool布尔型
     */
    bool isCompleteTree(TreeNode* root) {
        if(root==nullptr || (root->left==nullptr && root->right==nullptr)){
            return true;
        }
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty() && q.front()){
            int size=q.size();
            for(int i=0;i<size;++i){
                auto top=q.front();
                if(top==nullptr){
                    break;
                }else{
                    q.push(top->left);
                    q.push(top->right);
                }
                q.pop();
            }
        }
        while(!q.empty()){
            auto top=q.front();
            q.pop();
            if(top){
                return false;
            }
        }
        return true;
    }
};

//BM66 最长公共子串
/*
 *给定两个字符串str1和str2,输出两个字符串的最长公共子串
题目保证str1和str2的最长公共子串存在且唯一。 

数据范围： 1 \le |str1|,|str2| \le 50001≤∣str1∣,∣str2∣≤5000
要求： 空间复杂度 O(n^2)O(n 
2
 )，时间复杂度 O(n^2)O(n 
2
 )
 * */

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * longest common substring
     * @param str1 string字符串 the string
     * @param str2 string字符串 the string
     * @return string字符串
     */
    string LCS(string str1, string str2) {
        if(str1.size()==0 || str2.size()==0){
            return "";
        }
        int n=str1.size();
        int m=str2.size();
        vector<vector<int>> dp(n+1,vector<int>(m+1));
        int maxSubLength=0;
        int maxSubIndex=0;
        for(int i=0;i<n;++i){
            for(int j=0;j<m;++j){
                if(str1[i]==str2[j]){
                    dp[i+1][j+1]=dp[i][j]+1;
                    if(dp[i+1][j+1]>maxSubLength){
                        maxSubLength=dp[i+1][j+1];
                        maxSubIndex=i;
                    }
                }else{
                    dp[i+1][j+1]=0;
                }
            }
        }
        return str1.substr(maxSubIndex-maxSubLength+1,maxSubLength);
    }
};
