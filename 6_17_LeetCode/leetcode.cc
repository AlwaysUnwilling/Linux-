#include<iostream>
#include<vector>

using namespace std;

//1089. 复写零
/*
 *给你一个长度固定的整数数组 arr，请你将该数组中出现的每个零都复写一遍，并将其余的元素向右平移。

注意：请不要在超过该数组长度的位置写入元素。

要求：请对输入的数组 就地 进行上述修改，不要从函数返回任何东西。
*/

class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        if(arr.size()==0 || arr.size()==1){
            return ;
        }
        int n=arr.size();
        for(int i=0;i<n;++i){
            if(arr[i]==0 && i+1<n){
                int j=i+1;
                int end=n-1;
                while(end>j){
                    arr[end]=arr[end-1];
                    --end;
                }
                arr[j]=0;
                i+=1;
            }
        }
    }
};
//正反俩次遍历，原地修改
class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        int zeroSize=0;
        for(auto& e:arr){
            if(e==0){
                zeroSize++;
            }
        }
        int n=arr.size();
        for(int i=n-1;i>=0;--i){
            if(arr[i]==0){
                zeroSize--;
            }
            if(i+zeroSize<n){
                arr[i+zeroSize]=arr[i];
                if(arr[i]==0 && i+zeroSize+1<n){
                    arr[i+zeroSize+1]=0;
                }
            }
        }
    }
};


//剑指 Offer 36. 二叉搜索树与双向链表
/*
 *输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的循环双向链表。要求不能创建任何新的节点，只能调整树中节点指针的指向。
 * */

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};

class Solution {
public:
    void inOrder(Node* root)
    {
        if(root==nullptr){
            return ;
        }
        inOrder(root->left);
        if(pre!=nullptr){
            pre->right=root;
        }else{
            head=root;
        }
        root->left=pre;
        pre=root;
        inOrder(root->right);
    }
    Node* treeToDoublyList(Node* root) {
        if(root==nullptr){
            return root;
        }
        inOrder(root);
        head->left=pre;
        pre->right=head;
        return head;
    }
    Node* head;
    Node* pre;
};
