#include<iostream>
#include<vector>
#include<map>
#include<stack>
#include<limit.h>

using namespace std;

//508. 出现次数最多的子树元素和
/*
 *给你一个二叉树的根结点 root ，请返回出现次数最多的子树元素和。如果有多个元素出现的次数相同，返回所有出现次数最多的子树元素和（不限顺序）。

一个结点的 「子树元素和」 定义为以该结点为根的二叉树上所有结点的元素之和（包括结点本身）。
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

class Solution {
public:
    void SubTreeSum(TreeNode* root,int& sum)
    {
        if(root==nullptr){
            return;
        }
        sum+=root->val;
        SubTreeSum(root->left,sum);
        SubTreeSum(root->right,sum);
    }
    vector<int> findFrequentTreeSum(TreeNode* root) {
        if(root==nullptr){
            return {};
        }
        stack<TreeNode*> st;
        st.push(root);
        map<int,int> countMap;
        while(!st.empty()){
            int sum=0;
            auto node=st.top();
            st.pop();
            SubTreeSum(node,sum);
            countMap[sum]++;
            if(node->left && node->right){
                st.push(node->right);
                st.push(node->left);
            }else if(node->left){
                st.push(node->left);
            }else if(node->right){
                st.push(node->right);
            }
        }
        int maxCount=0;
        for(const auto& e:countMap){
            if(e.second>maxCount){
                maxCount=e.second;
            }
        }
        vector<int> ret;
        for(const auto& e:countMap){
            if(e.second==maxCount){
                ret.push_back(e.first);
            }
        }
        return ret;
    }
};

//剑指 Offer 67. 把字符串转换成整数
/*
 *写一个函数 StrToInt，实现把字符串转换成整数这个功能。不能使用 atoi 或者其他类似的库函数。
首先，该函数会根据需要丢弃无用的开头空格字符，直到寻找到第一个非空格的字符为止。
当我们寻找到的第一个非空字符为正或者负号时，则将该符号与之后面尽可能多的连续数字组合起来，作为该整数的正负号；假如第一个非空字符是数字，则直接将其与之后连续的数字字符组合起来，形成整数。
该字符串除了有效的整数部分之后也可能会存在多余的字符，这些字符可以被忽略，它们对于函数不应该造成影响。
注意：假如该字符串中的第一个非空格字符不是一个有效整数字符、字符串为空或字符串仅包含空白字符时，则你的函数不需要进行转换。
在任何情况下，若函数不能进行有效的转换时，请返回 0。
说明：
假设我们的环境只能存储 32 位大小的有符号整数，那么其数值范围为 [−231,  231 − 1]。如果数值超过这个范围，请返回  INT_MAX (231 − 1) 或 INT_MIN (−231) 。
 * */

class Solution {
public:
    int strToInt(string str) {
        if(str.size()==0){
            return 0;
        }
        int n=str.size();
        int flag=1;
        vector<int> vs;
        for(int i=0;i<n;++i){
            if(str[i]!=' '){
                if((str[i]>'9' || str[i]<'0') && (str[i]!='+' && str[i]!='-')){
                    break;
                }else if(str[i]>='0' && str[i]<='9'){
                    for(int j=i;j<n;++j){
                        if(str[j]>='0' && str[j]<='9'){
                            vs.push_back(str[j]-'0');
                        }else{
                            break;
                        }
                    }
                    break;
                }else if(str[i]=='+' || str[i]=='-'){
                    if(i+1<n && str[i+1]>='0' && str[i+1]<='9'){
                        flag=str[i]=='+'?flag:-1*flag;
                    }else{
                        break;
                    }
                }
            }
        }
        long long ret=0;
        for(int i=0;i<vs.size();++i){
            ret*=10;
            ret+=vs[i];
            if(flag==1 && ret>=(long long)INT_MAX){
                return INT_MAX;
            }
            if(flag==-1 && (-1*ret)<=(long long)INT_MIN){
                return INT_MIN;
            }
        }
        return ret*flag;
    }
};
