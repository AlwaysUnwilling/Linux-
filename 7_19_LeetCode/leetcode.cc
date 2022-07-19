#include<iostream>
#include<vector>

using namespace std;

//56. 合并区间
/*
 *以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。
 * */

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.size()==1){
            return intervals;
        }
        sort(intervals.begin(),intervals.end(),[](vector<int>& v1,vector<int>& v2){
            return v1[0] < v2[0];
        });
        vector<vector<int>> ans;
        vector<int> v(intervals[0]);
        for(int i=1;i < intervals.size();++i){
            if(intervals[i][0] <= v[1]){
                v[1]=max(intervals[i][1],v[1]);
            }else{
                ans.push_back(v);
                v=intervals[i];
            }
            if(i==intervals.size()-1){
                ans.push_back(v);
            }
        }
        return ans;
    }
};

//64. 最小路径和
/*
 *给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

说明：每次只能向下或者向右移动一步。
 * */
//动态规划
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m=grid.size();
        int n=grid[0].size();
        for(int i=1;i < m;++i){
            grid[i][0]+=grid[i-1][0];
        }
        for(int j=1;j < n;++j){
            grid[0][j]+=grid[0][j-1];
        }
        for(int i=1;i < m;++i){
            for(int j=1;j < n;++j){
                grid[i][j]+=min(grid[i-1][j],grid[i][j-1]);
            }
        }
        return grid[m-1][n-1];
    }
};
