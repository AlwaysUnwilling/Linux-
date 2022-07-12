#include<iostream>
#include<vector>
#include<string>

using namespace std;
//10. 正则表达式匹配
/*
 *给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。

'.' 匹配任意单个字符
'*' 匹配零个或多个前面的那一个元素
所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。
 * */

class Solution {
public:
    bool isMatch(string s, string p) {
    int row = s.size() + 1; // 表格行数
    int col = p.size() + 1; // 表格列数
    vector<vector<bool> > table(row, vector<bool>(col, false)); // 已自动给第一列为false
    table[0][0] = true; //第一个为true

    for (size_t j = 1; j < col; j++) {
        if (p[j - 1] == '*') { // 因为加了无符号，所以要减1
            table[0][j] = table[0][j - 2]; // 第一行赋值，不用管false的.默认
        }
    }

    for (size_t i = 1; i < row; i++) {
        for (size_t j = 1; j < col; j++) {
            if (p[j - 1] == s[i - 1] || p[j - 1] == '.') {
                table[i][j] = table[i - 1][j - 1];
            }
            else if (p[j - 1] == '*') {
                if (table[i][j - 2]) {
                    table[i][j] = true;
                } else if (p[j - 2] == s[i - 1] || p[j - 2] == '.') {
                    table[i][j] = table[i - 1][j];
                }
            }
        }
    }
    return table[row - 1][col - 1];
    }
};
