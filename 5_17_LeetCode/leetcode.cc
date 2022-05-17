#include<iostream>
#include<string>
#include<map>

using namespace std;

//953. 验证外星语词典
/*
 *某种外星语也使用英文小写字母，但可能顺序 order 不同。字母表的顺序（order）是一些小写字母的排列。

给定一组用外星语书写的单词 words，以及其字母表的顺序 order，只有当给定的单词在这种外星语中按字典序排列时，返回 true；否则，返回 false。
 * */
class Solution {
public:
    bool CompareString(const string& str1,const string& str2,map<char,int>& m)
    {
        int begin1=0;
        int begin2=0;
        while(begin1<str1.size() && begin2<str2.size()){
            if(m[str1[begin1]]>m[str2[begin2]]){
                return false;
            }else if(m[str1[begin1]]<m[str2[begin2]]){
                return true;
            }else{
                begin1++;
                begin2++;
            }
        }
        if(begin1<str1.size()){
            return false;
        }else{
            return true;
        }
    }
    bool isAlienSorted(vector<string>& words, string order) {
        if(words.size()==0 || words.size()==1){
            return true;
        }
        map<char,int> m;
        for(int i=0;i<order.size();++i){
            m[order[i]]=i;
        }
        string str=words[0];
        for(int i=1;i<words.size();++i){
            if(CompareString(str,words[i],m)){
                str=words[i];
            }else{
                return false;
            }
        }
        return true;
    }
};

//面试题 04.06. 后继者
/*
 *设计一个算法，找出二叉搜索树中指定节点的“下一个”节点（也即中序后继）。

如果指定节点没有对应的“下一个”节点，则返回null。
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
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        stack<TreeNode*> st;
        TreeNode *prev = nullptr, *curr = root;
        while (!st.empty() || curr != nullptr) {
            while (curr != nullptr) {
                st.emplace(curr);
                curr = curr->left;
            }
            curr = st.top();
            st.pop();
            if (prev == p) {
                return curr;
            }
            prev = curr;
            curr = curr->right;
        }
        return nullptr;
    }
};
