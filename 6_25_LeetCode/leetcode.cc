#include<iostream>
#include<vector>
#include<limits.h>
#include<algorithm>

using namespace std;

//剑指 Offer II 091. 粉刷房子
/*
 *假如有一排房子，共 n 个，每个房子可以被粉刷成红色、蓝色或者绿色这三种颜色中的一种，你需要粉刷所有的房子并且使其相邻的两个房子颜色不能相同。

当然，因为市场上不同颜色油漆的价格不同，所以房子粉刷成不同颜色的花费成本也是不同的。每个房子粉刷成不同颜色的花费是以一个 n x 3 的正整数矩阵 costs 来表示的。

例如，costs[0][0] 表示第 0 号房子粉刷成红色的成本花费；costs[1][2] 表示第 1 号房子粉刷成绿色的花费，以此类推。

请计算出粉刷完所有房子最少的花费成本。
 * */

//深度优先
class Solution {
public:
    void CostSum(vector<vector<int>>& costs,vector<int>& money,int& val,int color,int i)
    {
        if(i>=costs.size()){
            money.push_back(val);
            return;
        }
        for(int j=0;j<costs[0].size();++j){
            if(j==color){
                continue;
            }
            val+=costs[i][j];
            CostSum(costs,money,val,j,i+1);
            val-=costs[i][j];
        }
    }
    int minCost(vector<vector<int>>& costs) {
        if(costs.size()==0){
            return 0;
        }
        vector<int> money;
        int val=0;
        int color=-1;
        int i=0;
        CostSum(costs,money,val,color,i);
        int ret=INT_MAX;
        for(const auto& e:money){
            ret=min(ret,e);
        }
        return ret;
    }
};

//动态规划
class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        if(costs.size()==0){
            return 0;
        }
        vector<int> dp1(3);
        for(int i=0;i<3;++i){
            dp1[i]=costs[0][i];
        }
        int n=costs.size();
        for(int i=1;i<n;++i){
            vector<int> dp2(3);
            for(int j=0;j<3;++j){
                dp2[j]=min(dp1[(j+1)%3],dp1[(j+2)%3])+costs[i][j];
            }
            dp1=dp2;
        }
        int ret=dp1[0];
        for(int i=1;i<3;++i){
            ret=min(dp1[i],ret);
        }
        return ret;
    }
};
