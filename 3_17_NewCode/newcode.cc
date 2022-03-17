/*不同路径的数目(一):
 * 描述
一个机器人在m×n大小的地图的左上角（起点）。
机器人每次可以向下或向右移动。机器人要到达地图的右下角（终点）。
可以有多少种不同的路径从起点走到终点？

备注：m和n小于等于100,并保证计算结果在int范围内

数据范围：0 < n,m \le 1000<n,m≤100，保证计算结果在32位整型范围内
要求：空间复杂度 O(nm)O(nm)，时间复杂度 O(nm)O(nm)
进阶：空间复杂度 O(1)O(1)，时间复杂度 O(min(n,m))O(min(n,m))<Paste> 
*/

#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
      if (m < 1 || n < 1) {
         return 0;
      }
       // 申请F(i,j)空间，初始化
      vector<vector<int> > ret(m, vector<int>(n, 1));
      for (int i = 1; i < m; ++i) {
          for (int j = 1; j < n; ++j) {
            // F(i,j) = F(i-1,j) + F(i,j-1)
             ret[i][j] = ret[i - 1][j] + ret[i][j - 1];
          }
      }
      return ret[m - 1][n - 1];
    }
};
          
