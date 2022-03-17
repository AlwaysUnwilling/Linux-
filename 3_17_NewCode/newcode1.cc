/*最小路径和(Minimum Path Sum):
 * 题目描述：
  机器人要从网格左上角到达右下角，
  但是网格中添加了障碍物，障碍物用1表示
方法：动态规划
状态：
  子状态：从(0,0)到达(1,0),(1,1),(2,1),...(m-1,n-1)的路径数
  F(i,j): 从(0,0)到达F(i,j)的路径数
状态递推：
  F(i,j) = {F(i-1,j) + F(i,j-1)} OR {0, if obstacleGrid(i,j) = 1} 
初始化：
  特殊情况：第0行和第0列
  F(0,i) = {1} OR {0, if obstacleGrid(0,j) = 1, j <= i}
  F(i,0) = {1} OR {0, if obstacleGrid(j,0) = 1, j <= i}
返回结果：
  F(m-1,n-1)
*/

#include<iostream>
#include<vector>


using namespace std;

class Solution {
public:
 int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
    if (obstacleGrid.empty() || obstacleGrid[0].empty()) {
        return 0;
    }
    const int M = obstacleGrid.size();
    const int N = obstacleGrid[0].size();
    // // 申请F(i,j)空间，初始值为0
    vector<vector<int> > ret(M, vector<int>(N, 0));
    for (int i = 0; i < M; ++i) {
    // 第0列中只要前面有障碍，后面都无法到达
        if (obstacleGrid[i][0]) {
            break;
        }
        else {
            ret[i][0] = 1;
        }
    }
    for (int i = 0; i < N; ++i) {
    // // 第0行中只要前面有障碍，后面都无法到达
        if (obstacleGrid[0][i]) {
            break;
        }
        else {
            ret[0][i] = 1;
        }
    }
    for (int i = 1; i < M; ++i) {
        for (int j = 1; j < N; ++j) {
          // obstacleGrid[i][j] = 1 时，F(i,j)无法到达
          if (obstacleGrid[i][j]) {
              ret[i][j] = 0;
          }
          else {
          // F(i,j) = F(i-1,j) + F(i,j-1)
              ret[i][j] = ret[i - 1][j] + ret[i][j - 1];
          }
        }
    }
    return ret[M - 1][N - 1];
  }
};
