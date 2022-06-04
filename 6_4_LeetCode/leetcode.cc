#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

//剑指 Offer 32 - III. 从上到下打印二叉树 III

/*
请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行以此类推。
*/

// Definition for a binary tree node.
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> vv;
        if(root==nullptr){
            return vv;
        }
        queue<TreeNode*> q;
        q.push(root);
        int flag=1;
        while(!q.empty()){
            int size=q.size();
            vector<int> v;
            for(int i=0;i<size;++i){
                TreeNode* front=q.front();
                q.pop();
                v.push_back(front->val);
                if(front->left){
                    q.push(front->left);
                }
                if(front->right){
                    q.push(front->right);
                }
            }
            if(flag%2==0){
                reverse(v.begin(),v.end());
            }
            flag++;
            vv.push_back(v);
        }
        return vv;
    }
};

//929. 独特的电子邮件地址
/*
 *每个 有效电子邮件地址 都由一个 本地名 和一个 域名 组成，以 '@' 符号分隔。除小写字母之外，电子邮件地址还可以含有一个或多个 '.' 或 '+' 。

例如，在 alice@leetcode.com中， alice 是 本地名 ，而 leetcode.com 是 域名 。
如果在电子邮件地址的 本地名 部分中的某些字符之间添加句点（'.'），则发往那里的邮件将会转发到本地名中没有点的同一地址。请注意，此规则 不适用于域名 。

例如，"alice.z@leetcode.com” 和 “alicez@leetcode.com” 会转发到同一电子邮件地址。
如果在 本地名 中添加加号（'+'），则会忽略第一个加号后面的所有内容。这允许过滤某些电子邮件。同样，此规则 不适用于域名 。

例如 m.y+name@email.com 将转发到 my@email.com。
可以同时使用这两个规则。

给你一个字符串数组 emails，我们会向每个 emails[i] 发送一封电子邮件。返回实际收到邮件的不同地址数目。
 * */


class Solution {
public:
    void curString(const string& str,string& s1,string& s2,string sign)
    {
        size_t pos=str.find(sign);
        if(pos!=string::npos){
            s1=str.substr(0,pos);
            s2=str.substr(pos+1);
        }
    }
    int numUniqueEmails(vector<string>& emails) {
        if(emails.size()==0){
            return 0;
        }
        set<string> st;
        string newEmail;
        for(auto& str:emails){
            newEmail.clear();
            string s1,s2;
            curString(str,s1,s2,"@");
            for(int i=0;i<s1.size();++i){
                if(s1[i]!='.' && s1[i]!='+'){
                    newEmail+=s1[i];
                }else if(s1[i]=='+'){
                    break;
                }
            }
            newEmail+='@';
            newEmail+=s2;
            st.insert(newEmail);
        }
        return st.size();
    }
};
