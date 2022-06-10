#include<iostream>
#include<vector>
#include<stack>

using namespace std;

//JZ54 二叉搜索树的第k个节点
/*
 *给定一棵结点数为n 二叉搜索树，请找出其中的第 k 小的TreeNode结点值。
1.返回第k小的节点值即可
2.不能查找的情况，如二叉树为空，则返回-1，或者k大于n等等，也返回-1
3.保证n个节点的值不一样
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
     * @param proot TreeNode类 
     * @param k int整型 
     * @return int整型
     */
    void _KthNode(TreeNode* root,vector<int>& v)
    {
        if(root==nullptr){
            return ;
        }
        _KthNode(root->left,v);
        v.push_back(root->val);
        _KthNode(root->right,v);
    }
    int KthNode(TreeNode* proot, int k) {
        if(proot==nullptr || k==0){
            return -1;
        }
        vector<int> v;
        _KthNode(proot,v);
        if(v.size()<k){
            return -1;
        }else{
            return v[k-1];
        }
    }
};

//方法二：使用辅助栈模拟中序遍历
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param proot TreeNode类 
     * @param k int整型 
     * @return int整型
     */
    int KthNode(TreeNode* proot, int k) {
        if(proot==nullptr || k==0){
            return -1;
        }
        stack<TreeNode*> st;
        TreeNode* node=proot;
        st.push(node);
        int i=0;
        while(!st.empty()){
            //用栈模拟中序遍历：将左支树全部入栈
            while(node->left){
                st.push(node->left);
                node=node->left;
            }
            //左支树访问完毕->根
            i++;
            if(i==k){
                return st.top()->val;
            }
            TreeNode* tmp=st.top();
            st.pop();
            //右子树
            if(tmp->right){
                st.push(tmp->right);
                node=tmp->right;
            }
        }
        return -1;
    }
};

//JZ57 和为S的两个数字
/*
 *输入一个升序数组 array 和一个数字S，在数组中查找两个数，使得他们的和正好是S，如果有多对数字的和等于S，返回任意一组即可，如果无法找出这样的数字，返回一个空数组即可。
 * */

//方法一:哈希表
class Solution {
public:
    vector<int> FindNumbersWithSum(vector<int> array,int sum) {
        if(array.size()==0 || array.size()==1){
            return {};
        }
        unordered_map<int,int> hash;
        for(const auto& e:array){
            hash[e]++;
        }
        for(const auto& e:array){
            if(hash.find(sum-e)!=hash.end()){
                if(sum-e==e && hash[e]<2){
                    return {};
                }
                return {e,sum-e};
            }
        }
        return {};
    }
};

//方法二：双指针
class Solution {
public:
    vector<int> FindNumbersWithSum(vector<int> array,int sum) {
        vector<int> res;
        if(array.size()==0 || array.size()==1){
            return res;
        }
        int left=0,right=array.size()-1;
        while(left<right){
            if(array[left]+array[right]>sum){
                right--;
            }else if(array[left]+array[right]<sum){
                left++;
            }else{
                res.push_back(array[left]);
                res.push_back(array[right]);
                break;
            }
        }
        return res;
    }
};
