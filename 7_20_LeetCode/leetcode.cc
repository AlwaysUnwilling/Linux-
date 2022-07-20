#include<iostream>
#include<map>
#include<vector>

using namespace std;

//75. 颜色分类
/*
 *给定一个包含红色、白色和蓝色、共 n 个元素的数组 nums ，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

必须在不使用库的sort函数的情况下解决这个问题。
 * */

//计数排序
class Solution {
public:
    void sortColors(vector<int>& nums) {
        if(nums.size()==1){
            return ;
        }        
        map<int,int> countMap;
        for(auto& num:nums){
            countMap[num]++;
        }
        int i=0;
        for(auto& e:countMap){
            while(e.second--){
                nums[i++]=e.first;
            }
        }
    }
};

#include<string>

//79. 单词搜索
/*
 *给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
 * */

class Solution {
public:
    struct Pos
    {
        int x=0;
        int y=0;
    };
    bool IsPath(Pos& pos,int m,int n)
    {
        if(pos.x >= 0 && pos.x < m && pos.y >= 0 && pos.y < n){
            return true;
        }
        return false;
    }
    bool _exist(vector<vector<char>>& board, string& word,int m,int n,int length,int index,Pos pos,vector<vector<bool>>& visited)
    {
        if(board[pos.x][pos.y]!=word[index]){
            return false;
        }
        if(index==length-1){
            return true;
        }
        index++;
        visited[pos.x][pos.y]=true;
        Pos npos=pos;
        npos.x+=1;
        if(IsPath(npos,m,n) && !visited[npos.x][npos.y]){
            if(_exist(board,word,m,n,length,index,npos,visited)){
                return true;
            }
        }
        npos=pos;
        npos.x-=1;
        if(IsPath(npos,m,n) && !visited[npos.x][npos.y]){
            if(_exist(board,word,m,n,length,index,npos,visited)){
                return true;
            }
        }
        npos=pos;
        npos.y+=1;
        if(IsPath(npos,m,n) && !visited[npos.x][npos.y]){
            if(_exist(board,word,m,n,length,index,npos,visited)){
                return true;
            }
        }
        npos=pos;
        npos.y-=1;
        if(IsPath(npos,m,n) && !visited[npos.x][npos.y]){
            if(_exist(board,word,m,n,length,index,npos,visited)){
                return true;
            }
        }
        visited[pos.x][pos.y]=false;
        return false;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int m=board.size();
        int n=board[0].size();
        int length=word.size();
        vector<vector<bool>> visited(m,vector<bool>(n,false));
        Pos pos;
        for(int i=0;i < m;++i){
            for(int j=0;j < n;++j){
                pos.x=i;
                pos.y=j;
                if(_exist(board,word,m,n,length,0,pos,visited)){
                    return true;
                }
            }
        }
        return false;
    }
};
