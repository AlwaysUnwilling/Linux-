#include<iostream>
#include<string>
#include<vector>
#include<cmath>

using namespace std;

//剑指 Offer 13. 机器人的运动范围
/*
 *地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），也不能进入行坐标和列坐标的数位之和大于k的格子。例如，当k为18时，机器人能够进入方格 [35, 37] ，因为3+5+3+7=18。但它不能进入方格 [35, 38]，因为3+5+3+8=19。请问该机器人能够到达多少个格子？
 * */

class Solution {
public:
    bool isIn(vector<vector<int>>& map,int x,int y,int k)
    {
        int sumX=0,sumY=0;
        while(x){
            sumX+=x%10;
            x/=10;
        }
        while(y){
            sumX+=y%10;
            y/=10;
        }
        return (sumX+sumY)<=k;
    }
    bool isPath(vector<vector<int>>& map,vector<vector<int>>& visited,int m,int n,int x,int y,int k)
    {
        if(x>=0 && x<m && y>=0 && y<n && visited[x][y]==false && isIn(map,x,y,k)){
            return true;
        }
        return false;
    }
    void _movingCount(vector<vector<int>>& map,vector<vector<int>>& visited,int m,int n,int x,int y,int& count,int k)
    {
        if(visited[x][y]==false){
            count++;
            visited[x][y]=true;
        }

        if(isPath(map,visited,m,n,x-1,y,k)){
            _movingCount(map,visited,m,n,x-1,y,count,k);
        }
        if(isPath(map,visited,m,n,x+1,y,k)){
            _movingCount(map,visited,m,n,x+1,y,count,k);
        }
        if(isPath(map,visited,m,n,x,y-1,k)){
            _movingCount(map,visited,m,n,x,y-1,count,k);
        }
        if(isPath(map,visited,m,n,x,y+1,k)){
            _movingCount(map,visited,m,n,x,y+1,count,k);
        }
    }
    int movingCount(int m, int n, int k) {
        vector<vector<int>> map(m,vector<int>(n));
        int count=0;
        auto visited=map;
        _movingCount(map,visited,m,n,0,0,count,k);
        return count;
    }
};


//面试题 17.11. 单词距离
/*
 *有个内含单词的超大文本文件，给定任意两个不同的单词，找出在这个文件中这两个单词的最短距离(相隔单词数)。如果寻找过程在这个文件中会重复多次，而每次寻找的单词不同，你能对此优化吗?
 * */

class Solution {
public:
    int _findClosest(vector<string>& words,vector<int>& visited, string word1, string word2)
    {
        int index1=-1,index2=-1;
        int distance=INT_MAX;
        for(int i=0;i<words.size();++i){
            if(words[i]==word1 && visited[i]==0){
                index1=i;
                visited[i]=1;
            }
            if(words[i]==word2 && visited[i]==0){
                index2=i;
                visited[i]=1;
            }
            if(index1!=-1 && index2!=-1){
                distance=distance<abs(index2-index1)?distance:abs(index2-index1);
            }
        }
        return distance;
    }
    int findClosest(vector<string>& words, string word1, string word2) {
        vector<int> visited(words.size());
        return _findClosest(words,visited,word1,word2);
    }
};
