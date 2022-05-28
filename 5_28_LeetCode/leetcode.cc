#include<iostream>
#include<stack>
#include<string>

using namespace std;

//1021. 删除最外层的括号
/*
 *有效括号字符串为空 ""、"(" + A + ")" 或 A + B ，其中 A 和 B 都是有效的括号字符串，+ 代表字符串的连接。

例如，""，"()"，"(())()" 和 "(()(()))" 都是有效的括号字符串。
如果有效字符串 s 非空，且不存在将其拆分为 s = A + B 的方法，我们称其为原语（primitive），其中 A 和 B 都是非空有效括号字符串。

给出一个非空有效字符串 s，考虑将其进行原语化分解，使得：s = P_1 + P_2 + ... + P_k，其中 P_i 是有效括号字符串原语。

对 s 进行原语化分解，删除分解中每个原语字符串的最外层括号，返回 s 。
 * */

class Solution {
public:
    string removeOuterParentheses(string s) {
        if(s.size()==0){
            return nullptr;
        }
        stack<char> st;
        string ret;
        for(int i=0;i<s.size();++i){
            if(s[i]=='('){
                st.push(s[i]);
                if(st.size()>1){
                    ret+=s[i];
                }
            }else{
                st.pop();
                if(!st.empty()){
                    ret+=')';
                }
            }
        }
        return ret;
    }
};

剑指 Offer 26. 树的子结构
/*
 *输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)

B是A的子结构， 即 A中有出现和B相同的结构和节点值。
 * */


// Definition for a binary tree node.
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
    bool isEqualTree(TreeNode* A,TreeNode* B)
    {
        if(B==nullptr){
            return true;
        }
        if(A==nullptr || A->val!=B->val){
            return false;
        }

        return isEqualTree(A->left,B->left) && isEqualTree(A->right,B->right);
    }
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if(A==nullptr || B==nullptr){
            return false;
        }
        return isEqualTree(A,B) || isSubStructure(A->left,B) || isSubStructure(A->right,B);
    }
};
