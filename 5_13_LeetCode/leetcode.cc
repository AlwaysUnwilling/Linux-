#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<limits.h>

using namespace std;

//面试题 01.05. 一次编辑
/*
 *字符串有三种编辑操作:插入一个字符、删除一个字符或者替换一个字符。 给定两个字符串，编写一个函数判定它们是否只需要一次(或者零次)编辑。
 * */

class Solution {
public:
    int Distance(const string& s1,const string& s2)
    {
        int distance=0;
        for(int i=0;i<s1.size();++i){
            if(s1[i]!=s2[i]){
                distance++;
            }
        }
        return distance;
    }
    bool oneEditAway(string first, string second) {
        int firstSize=first.size();
        int secondSize=second.size();
        if(abs(firstSize-secondSize)>1){
            return false;
        }
        if(first==second){
            return true;
        }
        if(first.size()==0){
            return second.size()<2?true:false;
        }
        if(second.size()==0){
            return first.size()<2?true:false;
        }
        if(first.size()==second.size()){
            return Distance(first,second)>1?false:true;
        }
        string shorter=first;
        string longer=second;
        if(first.size()>second.size()){
            shorter=second;
            longer=first;
        }
        int size=shorter.size();
        int begin=0;
        for(int i=0;i<size;++i){
            size_t index=longer.find(shorter[i],begin);
            if(index==string::npos){
                return false;
            }else{
                begin=index+1;
            }
        }
        return true;
    }
};

//449. 序列化和反序列化二叉搜索树
/*
 *序列化是将数据结构或对象转换为一系列位的过程，以便它可以存储在文件或内存缓冲区中，或通过网络连接链路传输，以便稍后在同一个或另一个计算机环境中重建。

设计一个算法来序列化和反序列化 二叉搜索树 。 对序列化/反序列化算法的工作方式没有限制。 您只需确保二叉搜索树可以序列化为字符串，并且可以将该字符串反序列化为最初的二叉搜索树。

编码的字符串应尽可能紧凑。
 * */

// Definition for a binary tree node.
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Codec {
public:
    string serialize(TreeNode* root) {
        string res;
        vector<int> arr;
        postOrder(root, arr);
        if (arr.size() == 0) {
            return res;
        }
        for (int i = 0; i < arr.size() - 1; i++) {
            res.append(to_string(arr[i]) + ",");
        }
        res.append(to_string(arr.back()));
        return res;
    }

    vector<string> split(const string &str, char dec) {
        int pos = 0;
        int start = 0;
        vector<string> res;
        while (pos < str.size()) {
            while (pos < str.size() && str[pos] == dec) {
                pos++;
            }
            start = pos;
            while (pos < str.size() && str[pos] != dec) {
                pos++;
            }
            if (start < str.size()) {
                res.emplace_back(str.substr(start, pos - start));
            }
        }
        return res;
    }

    TreeNode* deserialize(string data) {
        if (data.size() == 0) {
            return nullptr;
        }
        vector<string> arr = split(data, ',');
        stack<int> st;
        for (auto & str : arr) {
            st.emplace(stoi(str));
        }
        return construct(INT_MIN, INT_MAX, st);
    }

    void postOrder(TreeNode *root,vector<int> & arr) {
        if (root == nullptr) {
            return;
        }
        postOrder(root->left, arr);
        postOrder(root->right, arr);
        arr.emplace_back(root->val);
    }

    TreeNode * construct(int lower, int upper, stack<int> & st) {
        if (st.size() == 0 || st.top() < lower || st.top() > upper) {
            return nullptr;
        }
        int val = st.top();
        st.pop();
        TreeNode *root = new TreeNode(val);
        root->right = construct(val, upper, st);
        root->left = construct(lower, val, st);
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;
