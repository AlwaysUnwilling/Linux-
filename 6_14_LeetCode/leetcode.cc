#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//498. 对角线遍历
/*
 *给你一个大小为 m x n 的矩阵 mat ，请以对角线遍历的顺序，用一个数组返回这个矩阵中的所有元素。
 * */

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        if(mat.size()==0){
            return {};
        }
        if(mat.size()==1){
            return mat[0];
        }
        vector<int> res;
        int n=mat.size();
        int m=mat[0].size();
        
        int flag=0;
        for(int i=0;i<n;++i){
            int k=i;
            int j=0;
            vector<int> tmp;
            while(k>=0 && j<m){
                tmp.push_back(mat[k][j]);
                k--;
                j++;
            }
            if(flag%2){
                reverse(tmp.begin(),tmp.end());
            }
            flag++;
            for(auto& e:tmp){
                res.push_back(e);
            }
        }
        for(int i=1;i<m;++i){
            int j=n-1;
            int k=i;
            vector<int> tmp;
            while(j>=0 && k<m){
                tmp.push_back(mat[j][k]);
                j--;
                k++;
            }
            if(flag%2){
                reverse(tmp.begin(),tmp.end());
            }
            flag++;
            for(auto&  e:tmp){
                res.push_back(e);
            }
        }
        return res;
    }
};

//剑指 Offer 45. 把数组排成最小的数
/*
 *输入一个非负整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。
 * */
#include<queue>

class Solution {
public:
    struct myCompare
    {
        bool operator()(const string& s1,const string& s2)
        {
            return s1+s2>s2+s1;
        }
    };
    string minNumber(vector<int>& nums) {
        string res;
        priority_queue<string,vector<string>,myCompare> pq;
        for(const auto& e:nums){
            pq.push(to_string(e));
        }
        while(!pq.empty()){
            string num=pq.top();
            pq.pop();
            res+=num;
        }
        return res;
    }
};
