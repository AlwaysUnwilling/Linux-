#include<iostream>
#include<string>
#include<stack>
#include<vector>

using namespace std;

//388. 文件的最长绝对路径
/*
 *假设有一个同时存储文件和目录的文件系统。这里将 dir 作为根目录中的唯一目录。dir 包含两个子目录 subdir1 和 subdir2 。subdir1 包含文件 file1.ext 和子目录 subsubdir1；subdir2 包含子目录 subsubdir2，该子目录下包含文件 file2.ext 。给定一个以上述格式表示文件系统的字符串 input ，返回文件系统中 指向 文件 的 最长绝对路径 的长度 。 如果系统中没有文件，返回 0。
 * */

//方法一：栈
class Solution {
public:
    int lengthLongestPath(string input) {
        int n = input.size();
        int pos = 0;
        int ret = 0;
        stack<int> st;

        while (pos < n) {
            /* 检测当前文件的深度 */
            int depth = 1;
            while (pos < n && input[pos] == '\t') {
                pos++;
                depth++;
            }
            /* 统计当前文件名的长度 */   
            int len = 0; 
            bool isFile = false;     
            while (pos < n && input[pos] != '\n') {
                if (input[pos] == '.') {
                    isFile = true;
                }
                len++;
                pos++;
            }
            /* 跳过换行符 */
            pos++;

            while (st.size() >= depth) {
                st.pop();
            }
            if (!st.empty()) {
                len += st.top() + 1;
            }
            if (isFile) {
                ret = max(ret, len);
            } else {
                st.emplace(len);
            }
        }
        return ret;
    }
};

// 方法二：遍历

class Solution2 {
public:
    int lengthLongestPath(string input) {
        int n = input.size();
        int pos = 0;
        int ret = 0;
        vector<int> level(n + 1);

        while (pos < n) {
            /* 检测当前文件的深度 */
            int depth = 1;
            while (pos < n && input[pos] == '\t') {
                pos++;
                depth++;
            }
            /* 统计当前文件名的长度 */   
            int len = 0; 
            bool isFile = false;     
            while (pos < n && input[pos] != '\n') {
                if (input[pos] == '.') {
                    isFile = true;
                }
                len++;
                pos++;
            }
            /* 跳过换行符 */
            pos++;

            if (depth > 1) {
                len += level[depth - 1] + 1;
            }
            if (isFile) {
                ret = max(ret, len);
            } else {
                level[depth] = len;
            }
        }
        return ret;
    }
};
