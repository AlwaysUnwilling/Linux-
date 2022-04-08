#include<iostream>
#include<vector>
#include<queue>

using namespace std;

//N 叉树的层序遍历:
//给定一个 N 叉树，返回其节点值的层序遍历。（即从左到右，逐层遍历）


// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
 

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> vv;
        if(root==nullptr){
            return vv;
        }
        queue<Node*> q;
        q.push(root);
        while(!q.empty()){
            int size=q.size();
            vector<int> v;
            while(size--){
                Node* front=q.front();
                v.push_back(front->val);
                q.pop();
                if(front->children.size()!=0){
                    for(auto e:front->children){
                        q.push(e);
                    }
                }
            }
            vv.push_back(v);
        }
        return vv;
    }
};
