#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//JZ41 数据流中的中位数
/*
 *如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。我们使用Insert()方法读取数据流，使用GetMedian()方法获取当前读取数据的中位数。
 * */

//方法一：数组

class Solution {
public:
    void Insert(int num) {
        v.push_back(num);
    }

    double GetMedian() { 
        if(v.size()==1){
            return v[0];
        }
        sort(v.begin(),v.end());
        int count=v.size();
        return count%2==0?
            1.0*(v[(count-1)/2]+v[(count-1)/2+1])/2:
            1.0*(v[(count-1)/2]);
    }
private:
    vector<int> v;
};

//方法二：插入排序

class Solution {
public:
    void Insert(int num) {
        int pos=0;
        while(pos<v.size()){
            if(num<v[pos]){
                break;
            }
            ++pos;
        }
        if(pos>=v.size()){
            v.push_back(num);
        }else{
            int end=v.size()-1;
            int tmp=v[end];
            while(end>pos){
                v[end]=v[end-1];
                --end;
            }
            v[end]=num;
            v.push_back(tmp);
        }
    }

    double GetMedian() { 
        int count=v.size();
        if(count==1){
            return v[0];
        }
        return count%2==0?
            1.0*(v[(count-1)/2]+v[(count-1)/2+1])/2:
            1.0*(v[(count-1)/2]);
    }
private: 
    vector<int> v;
};

//JZ8 二叉树的下一个结点
/*
 *描述
给定一个二叉树其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。注意，树中的结点不仅包含左右子结点，同时包含指向父结点的next指针。下图为一棵有9个节点的二叉树。树中从父节点指向子节点的指针用实线表示，从子节点指向父节点的用虚线表示
 * */

struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {
        
    }
};

class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode) {
        if(pNode->right){
            auto node=pNode->right;
            while(node->left){
                node=node->left;
            }
            return node;
        }
        auto parent=pNode->next;
        if(parent==nullptr){
            return parent;
        }
        if(parent->left==pNode){
            return parent;
        }else{
            while(parent && parent->right==pNode){
                pNode=parent;            
                parent=parent->next;
            }
            return parent;
        }
    }
};

