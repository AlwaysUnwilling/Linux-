#include<iostream>
#include<unordered_map>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

//49. 字母异位词分组
/*
 *给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。

字母异位词 是由重新排列源单词的字母得到的一个新单词，所有源单词中的字母通常恰好只用一次
 * */

//暴力排序解法
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> ret;
        for(const auto& str:strs){
            string tmp2=str;
            sort(tmp2.begin(),tmp2.end());
            bool flag=false;
            for(int i=0;i < (int)ret.size();++i){
                string tmp1=ret[i][0];
                sort(tmp1.begin(),tmp1.end());
                if(tmp1==tmp2){
                    flag=true;
                    ret[i].push_back(str);
                }
            }
            if(!flag){
                ret.push_back({str});
            }
        }
        return ret;
    }
};

////哈希表---排序
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,vector<string>> strMap;
        //遍历strs每个元素法人拷贝对象排序后插入到strMap中
        for(const auto& str:strs){
            string tmp=str;
            sort(tmp.begin(),tmp.end());
            strMap[tmp].push_back(str);
        }
        //导出strMap中的结果
        vector<vector<string>> ret;
        for(const auto& sm:strMap){
            ret.push_back(sm.second);
        }
        return ret;
    }
};

//96. 不同的二叉搜索树
/*
 * 给你一个整数 n ，求恰由 n 个节点组成且节点值从 1 到 n 互不相同的 二叉搜索树 有多少种？返回满足题意的二叉搜索树的种数。
 *
 * */
//动态规划：假设以i为根节点的二叉树，那么它的左子树的节点个数是i-1；右子树的节点个数是n-i个
//         即：以i为根节点的二叉树的个数res(i)=i-1个节点的二叉树的个数 * n-i个节点的二叉树个数
//         所有的以1-n为节点的二叉树的个数的和即为所求
class Solution {
public:
    int numTrees(int n) {
        vector<int> res(n+1,0);
        res[0]=1;
        res[1]=1;
        for(int i=2;i < n+1;++i){
            for(int j=1;j <= i;j++){
                res[i]+=res[j-1]*res[i-j];
            }
        }
        return res[n];
    }
};
