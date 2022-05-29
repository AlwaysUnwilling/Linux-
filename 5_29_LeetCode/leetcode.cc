#include<iostream>
#include<vector>
#include<string>
#include<queue>

using namespace std;

//468. 验证IP地址
/*
 *给定一个字符串 queryIP。如果是有效的 IPv4 地址，返回 "IPv4" ；如果是有效的 IPv6 地址，返回 "IPv6" ；如果不是上述类型的 IP 地址，返回 "Neither" 。

有效的IPv4地址 是 “x1.x2.x3.x4” 形式的IP地址。 其中 0 <= xi <= 255 且 xi 不能包含 前导零。例如: “192.168.1.1” 、 “192.168.1.0” 为有效IPv4地址， “192.168.01.1” 为无效IPv4地址; “192.168.1.00” 、 “192.168@1.1” 为无效IPv4地址。

一个有效的IPv6地址 是一个格式为“x1:x2:x3:x4:x5:x6:x7:x8” 的IP地址，其中:

1 <= xi.length <= 4
xi 是一个 十六进制字符串 ，可以包含数字、小写英文字母( 'a' 到 'f' )和大写英文字母( 'A' 到 'F' )。
在 xi 中允许前导零。
 * */

class Solution {
public:
    bool IsIPv4(string& queryIP)
    {
        vector<string> vs;
        string tmp;
        int count=0;
        for(int i=0;i<queryIP.size();++i){
            if(queryIP[i]!='.'){
                tmp+=queryIP[i];
            }else{
                count++;
                vs.push_back(tmp);
                tmp.clear();
            }
        }
        if(tmp.size()!=0){
            vs.push_back(tmp);
        }
        if(vs.size()!=4 || count!=3){
            return false;
        }else{
            for(auto& str:vs){
                if(str.size()==0){
                    return false;
                }
                for(auto& e:str){
                    if(e>'9' || e<'0'){
                        return false;
                    }
                }
                if((str.size()>1 && str[0]=='0') || (atoi(str.c_str())<0 || atoi(str.c_str())>255)){
                    return false;
                }
            }
        }
        return true;
    }
    bool IsIPv6(string& queryIP)
    {
        vector<string> vs;
        string tmp;
        int count=0;
        for(int i=0;i<queryIP.size();++i){
            if(queryIP[i]!=':'){
                tmp+=queryIP[i];
            }else{
                count++;
                vs.push_back(tmp);
                tmp.clear();
            }
        }
        if(tmp.size()!=0){
            vs.push_back(tmp);
        }
        if(vs.size()!=8 || count!=7){
            return false;
        }else{
            for(auto& str:vs){
                if(str.size()==0 || str.size()>4){
                    return false;
                }
                for(auto& e:str){
                    if(!(e>='0' && e<='9') && !(e>='a' && e<='f') && !(e>='A' && e<='F')){
                        return false;
                    }
                }
            }
        }
        return true;
    }
    string validIPAddress(string queryIP) {
        if(queryIP.size()==0){
            return "Neither";
        }
        if(queryIP.find(':')==string::npos && queryIP.find('.')==string::npos){
            return "Neither";
        }    
        if(!IsIPv4(queryIP) && !IsIPv6(queryIP)){
            return "Neither";
        }else if(IsIPv4(queryIP)){
            return "IPv4";
        }else{
            return "IPv6";
        }
    }
};

//剑指 Offer 32 - I. 从上到下打印二叉树
/*
 *从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。
 * */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> levelOrder(TreeNode* root) {
        vector<int> ans;
        if(root==nullptr){
            return ans;
        }
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int size=q.size();
            for(int i=0;i<size;++i){
                auto front=q.front();
                q.pop();
                ans.push_back(front->val);
                if(front->left){
                    q.push(front->left);
                }
                if(front->right){
                    q.push(front->right);
                }
            }
        }
        return ans;
    }
};
