#include<iostream>
#include<vector>

using namespace std;


//[编程题]左右最值最大差
/*
给定一个长度为N(N>1)的整型数组A，可以将A划分成左右两个部分，左部分A[0..K]，右部分A[K+1..N-1]，K可以取值的范围是[0,N-2]。求这么多划分方案中，左部分中的最大值减去右部分最大值的绝对值，最大是多少？
给定整数数组A和数组的大小n，请返回题目所求的答案。
 * */

class MaxGap {
public:
    int findMaxGap(vector<int> A, int n) {
        // write code here
        int mx = A[0];
        //全局最大值
        for(int& e : A)
            mx = max(mx, e);
        return mx - min(A[0], A[n - 1]);
    }
};


//[编程题]顺时针打印矩阵
/*
 *对于一个矩阵，请设计一个算法从左上角(mat[0][0])开始，顺时针打印矩阵元素。
给定int矩阵mat,以及它的维数nxm，请返回一个数组，数组中的元素为矩阵元素的顺时针输出。
 * */
class Printer {
public:
    vector<int> clockwisePrint(vector<vector<int> > mat, int n, int m) {
        // write code here
        //左上角坐标
        int x1 = 0;
        int y1 = 0;
        //右下角坐标
        int x2 = n - 1;
        int y2 = m - 1;
        vector<int> ret;
        while(x1 <= x2 && y1 <= y2)
        {
            //第一行: x1, y1 ~ y2
            for(int i = y1; i <= y2; ++i)
                ret.push_back(mat[x1][i]);
            //最后一列：x1 + 1 ~ x2, y2
            for(int i = x1 + 1; i <= x2; ++i)
                ret.push_back(mat[i][y2]);
            //最后一行: x2, y2 - 1 ~ y1  --> x1 < x2
            if(x1 < x2)
            {
                for(int i = y2 - 1; i >= y1; --i)
                    ret.push_back(mat[x2][i]);
            }
            //第一列：x2 - 1 ~ x1 + 1, y1 --> y1 < y2
            if(y1 < y2)
            {
                for(int i = x2 - 1; i > x1; --i)
                    ret.push_back(mat[i][y1]);
            }
            
            x1++;
            y1++;
            x2--;
            y2--;
        }
        return ret;
    }
};
