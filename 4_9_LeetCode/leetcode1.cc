#include<iostream>

using namespace std;

//780. 到达终点:
//给定四个整数 sx , sy ，tx 和 ty，如果通过一系列的转换可以从起点 (sx, sy) 到达终点 (tx, ty)，则返回 true，否则返回 false。从点 (x, y) 可以转换到 (x, x+y)  或者 (x+y, y)。

// 反向计算:如果从 (sx,sy) 开始正向计算，则可能的情况非常多，会超出时间限制。注意到sx,sy,tx,ty 都是正整数，因此对于给定的状态(tx,ty)，只有当 tx!=ty时才存在上一个状态，且上一个状态唯一，可能情况如下：
// 如果tx==ty，不存在上一个状态，状态 (tx,ty) 即为起点状态；
// 如果 tx>ty，则上一个状态是(tx−ty,ty)；
// 如果tx<ty，则上一个状态是(tx,ty−tx)。




class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        while (tx > sx && ty > sy && tx != ty) {
            if (tx > ty) {
                tx %= ty;
            } else {
                ty %= tx;
            }
        }
        if (tx == sx && ty == sy) {
            return true;
        } else if (tx == sx) {
            return ty > sy && (ty - sy) % tx == 0;
        } else if (ty == sy) {
            return tx > sx && (tx - sx) % ty == 0;
        } else {
            return false;
        }
    }
};

