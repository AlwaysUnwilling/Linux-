#include<iostream>
#include<vector>


using namespace std;

//剑指 Offer 12. 矩阵中的路径
/*
 *给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
 * */

class Solution {
public:
    bool DoMatch(vector<vector<char>>& board,vector<vector<int>>& visited,int x,int y,char ch)
    {
        return x>=0 && x<board.size() && y>=0 && y<board[0].size() && ch==board[x][y] && visited[x][y]==false;
    }
    bool CanFindWord(vector<vector<char>>& board,vector<vector<int>>& visited,int x,int y,const string& word,int wIndex)
    {
        if(wIndex==word.size()-1){
            return true;
        }
        visited[x][y]=true;
        //(x-1,y)
        if(DoMatch(board,visited,x-1,y,word[wIndex+1])){
            if(CanFindWord(board,visited,x-1,y,word,wIndex+1)){
                return true;
            }
        }
        //(x+1,y)
        if(DoMatch(board,visited,x+1,y,word[wIndex+1])){
            if(CanFindWord(board,visited,x+1,y,word,wIndex+1)){
                return true;
            }
        }
        //(x,y+1)
        if(DoMatch(board,visited,x,y+1,word[wIndex+1])){
            if(CanFindWord(board,visited,x,y+1,word,wIndex+1)){
                return true;
            }
        }
        //(x,y-1)
        if(DoMatch(board,visited,x,y-1,word[wIndex+1])){
            if(CanFindWord(board,visited,x,y-1,word,wIndex+1)){
                return true;
            }
        }
        visited[x][y]=false;
        return false;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int windex=0;
        int m=board.size();
        int n=board[0].size();
        vector<vector<int>> visited(m,vector<int>(n));
        for(int i=0;i<board.size();++i){
            for(int j=0;j<board[0].size();++j){
                if(board[i][j]==word[0]){
                    if(CanFindWord(board,visited,i,j,word,windex)){
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

//剑指 Offer 04. 二维数组中的查找
/*
 *在一个 n * m 的二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个高效的函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
 * */

class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        if(matrix.size()==0){
            return false;
        }
        int endj=matrix[0].size()-1;
        int endi=0;
        while(endi<matrix.size() && endj>=0){
            if(matrix[endi][endj]==target){
                return true;
            }else if(matrix[endi][endj]>target){
                endj--;
            }else{
                endi++;
            }
        }
        return false;
    }
};


