/*************************************************************************
	> File Name: newcode1.c
	> Author: 
	> Mail: 
	> Created Time: Mon 14 Mar 2022 11:07:42 PM CST
    > About:动态规划---三角形:描述
给出一个三角形，计算从三角形顶部到底部的最小路径和，每一步都可以移动到下面一行相邻的数字，
例如，给出的三角形如下：
[[20],[30,40],[60,50,70],[40,10,80,30]]
最小的从顶部到底部的路径和是20 + 30 + 50 + 10 = 110。
注意：
如果你能只用O（N）的额外的空间来完成这项工作的话，就可以得到附加分，其中N是三角形中的行总数。
 ************************************************************************/

#include<stdio.h>
class Solution {
public:
 int minimumTotal(vector<vector<int>> &triangle) {
        if (triangle.empty()){
            return 0;
        }
        // F[i][j], F[0][0]初始化
        vector<vector<int>> min_sum(triangle);
        int line = triangle.size();
        for (int i = 1; i < line; i++){
            for (int j = 0; j <= i; j++){
                // 处理左边界和右边界
                if (j == 0){
                    min_sum[i][j] = min_sum[i - 1][j];
                }
                else if (j == i){
                    min_sum[i][j] = min_sum[i - 1][j - 1];
                }
                else{
                    min_sum[i][j] = min(min_sum[i - 1][j], min_sum[i - 1][j - 1]);
                }
                // F(i,j) = min( F(i-1, j-1), F(i-1, j)) + triangle[i][j]
                min_sum[i][j] = min_sum[i][j] + triangle[i][j];
            }
        }
        int result = min_sum[line - 1][0];
        // min(F(n-1, i))
        for (int i = 1; i < line; i++){
            result = min(min_sum[line - 1][i], result);
        }
        return result;
    }
};

/*
方法二：动态规划（反向思维）
状态：
  子状态：从(n,n),(n,n-1),...(1,0),(1,1),(0,0)到最后一行的最短路径和
  F(i,j): 从(i,j)到最后一行的最短路径和
状态递推：
  F(i,j) = min( F(i+1, j), F(i+1, j+1)) + triangle[i][j]
初始值：
  F(n-1,0) = triangle[n-1][0], F(n-1,1) = triangle[n-1][1],..., F(n-1,n-1) = triangle[n-
1][n-1]
返回结果：
  F(0, 0)
  
这种逆向思维不需要考虑边界，也不需要最后寻找最小值，直接返回F(0,0)即可
*/
class Solution2 {
public:
    int minimumTotal(vector<vector<int>> &triangle) {
        if (triangle.empty()){
            return 0;
        }
        // F[n-1][n-1],...F[n-1][0]初始化
        vector<vector<int>> min_sum(triangle);
        int line = triangle.size();
        // 从倒数第二行开始
        for (int i = line - 2; i >= 0; i--){
            for (int j = 0; j <= i; j++){
                // F(i,j) = min( F(i+1, j), F(i+1, j+1)) + triangle[i][j]
                min_sum[i][j] = min(min_sum[i + 1][j], min_sum[i + 1][j + 1]) +
                triangle[i][j];
            }
        }
        return min_sum[0][0];
    }
};
