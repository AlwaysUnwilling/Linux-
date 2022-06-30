#include<iostream>
#include<vector>


using namespace std;

//NC45 实现二叉树先序，中序和后序遍历
/*
 *给定一棵二叉树，分别按照二叉树先序，中序和后序打印所有的节点。

数据范围：0 \le n \le 10000≤n≤1000，树上每个节点的val值满足 0 \le val \le 1000≤val≤100
要求：空间复杂度 O(n)O(n)，时间复杂度 O(n)O(n)
 * */

//递归实现 时间复杂度不满足

struct TreeNode {
  int val;
	struct TreeNode *left;
	struct TreeNode *right;
};


class Solution {
public:
    /**
     * 
     * @param root TreeNode类 the root of binary tree
     * @return int整型vector<vector<>>
     */
    void PreOrder(TreeNode* root,vector<int>& Pre)
    {
        if(root==nullptr){
            return ;
        }
        Pre.push_back(root->val);
        PreOrder(root->left,Pre);
        PreOrder(root->right,Pre);
    }
    void InOrder(TreeNode* root,vector<int>& In)
    {
        if(root==nullptr){
            return ;
        }
        InOrder(root->left,In);
        In.push_back(root->val);
        InOrder(root->right,In);
    }
    void PostOrder(TreeNode* root,vector<int>& Post)
    {
        if(root==nullptr){
            return ;
        }
        PostOrder(root->left,Post);
        PostOrder(root->right,Post);
        Post.push_back(root->val);
    }
    vector<vector<int> > threeOrders(TreeNode* root) {
        if(root==nullptr){
            return {{},{},{}};
        }
        vector<vector<int>> vv;
        vector<int> v;
        PreOrder(root,v);
        vv.push_back(v);
        v.clear();
        InOrder(root,v);
        vv.push_back(v);
        v.clear();
        PostOrder(root,v);
        vv.push_back(v);
        return vv;
    }
};

//非递归 O(N)
class Solution {
public:
    vector<int> pre;
    vector<int> mid;
    vector<int> post;
    vector<vector<int> > threeOrders(TreeNode* root) {
        // write code here
        if(root != nullptr){//nullptr任意指针类型
            preorder(root);
            midorder(root);
            postorder(root);
        }
        vector<vector<int>>res = {pre,mid,post};
        return res;
    }
    vector<int> preorder(TreeNode* root) {//中左右
        if(root==NULL){
            return pre;
        }
        stack<TreeNode*> tmp;//设置栈对象
        tmp.push(root);//保存根结点
        while(!tmp.empty()){
            auto x = tmp.top();
            tmp.pop();//出栈
            pre.push_back(x->val);//存入容器
            if(x->right){
                tmp.push(x->right);
            }
            if(x->left){
                tmp.push(x->left);
            }
        }
        return pre;
    }
    vector<int> midorder(TreeNode* root) {//左中右
        stack<TreeNode *> s;//设置栈对象
        while (s.size() || root){
            while (root){
                s.push(root);
                root = root->left;//先左
            }
            if (s.size()){
                root = s.top();
                s.pop();
                mid.push_back(root->val);
                root = root->right;
            }
        }
        return mid;
}
    vector<int> postorder(TreeNode* root) {//左右中
        if(root==NULL){
            return post;
        }
        stack<TreeNode*> tmp;//设置栈对象
        tmp.push(root);
        while(!tmp.empty()){
            auto x = tmp.top();
            tmp.pop();
            post.push_back(x->val);
            if(x->left){
                tmp.push(x->left);
            }
            if(x->right){
                tmp.push(x->right);
            }
        }
        reverse(post.begin(),post.end());
        return post;
    }
};


//NC78 反转链表
/*
 *描述
给定一个单链表的头结点pHead(该头节点是有值的，比如在下图，它的val是1)，长度为n，反转该链表后，返回新链表的表头。

数据范围： 0\leq n\leq10000≤n≤1000
要求：空间复杂度 O(1)O(1) ，时间复杂度 O(n)O(n) 。

如当输入链表{1,2,3}时，
经反转后，原链表变为{3,2,1}，所以对应的输出为{3,2,1}。
 * */


struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};
class Solution {
public:
    ListNode* ReverseList(ListNode* pHead) {
        if(pHead==nullptr || pHead->next==nullptr){
            return pHead;
        }
        ListNode* Pre=NULL;
        ListNode* Cur=pHead;
        ListNode* Next=Cur->next;
        while(Next){
            Cur->next=Pre;
            Pre=Cur;
            Cur=Next;
            Next=Cur->next;
        }
        Cur->next=Pre;
        return Cur;
    }
};
