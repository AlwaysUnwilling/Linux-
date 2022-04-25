#include<iostream>
#include<vector>
#include<stack>

using namespace std;


//【年终奖】
/*
 *【年终奖】
小东所在公司要发年终奖，而小东恰好获得了最高福利，他要在公司年会上参与一个抽奖游戏，游戏在一个6*6的棋盘上进行，上面放着36个价值不等的礼物，每个
小的棋盘上面放置着一个礼物，他需要从左上角开始游戏，每次只能向下或者向右移动一步，到达右下角停止，一路上的格子里的礼物小东都能拿到，请设计一个算
法使小东拿到价值最高的礼物。
给定一个6*6的矩阵board，其中每个元素为对应格子的礼物价值,左上角为[0,0],请返回能获得的最大价值，保证每个礼物价值大于100小于1000
 * */

class Bonus {
  public:
    int getMost(vector<vector<int> > board) {
    int n=board.size();
    int m=board[0].size();
    for(int i=1;i<n;++i)
    {
      board[i][0]=board[i-1][0]+board[i][0];
    }
    for(int i=1;i<m;++i)
    {
      board[0][i]=board[0][i-1]+board[0][i];
    }
    for(int i=1;i<n;++i)
    {
      for(int j=1;j<m;++j)
      {
        board[i][j]=max(board[i-1][j],board[i][j-1])+board[i][j];
      }
    }
    return board[n-1][m-1];
  }
};

//【迷宫问题】

/*
 *定义一个二维数组 N*M ，如 5 × 5 数组下所示：
int maze[5][5] = {
0, 1, 0, 0, 0,
0, 1, 1, 1, 0,
0, 0, 0, 0, 0,
0, 1, 1, 1, 0,
0, 0, 0, 1, 0,
};
它表示一个迷宫，其中的1表示墙壁，0表示可以走的路，只能横着走或竖着走，不能斜着走，要求编程序找出从左上角到右下角的路线。入口点为[0,0],既第一格是
可以走的路
 * */

bool IsPath(vector<vector<int>>& vv,int x,int y,int n,int m)
{
  if(x>=0 && x<n && y>=0 && y<m && vv[x][y]==0){
  return true;
  }
  return false;
}
bool RunMaze(vector<vector<int>>& vv,stack<pair<int,int>>& pos,int x,int y,int n,int m)
{
  pos.push({x,y});
  if(x==n-1 && y==m-1){
    return true;
  }
  vv[x][y]=-1;
  if(IsPath(vv,x-1,y,n,m)){
    auto ret=RunMaze(vv,pos,x-1,y,n,m);
    if(ret){
      return true;
    }
  }
  if(IsPath(vv,x+1,y,n,m)){
    auto ret=RunMaze(vv,pos,x+1,y,n,m);
    if(ret){
      return true;
    }
  }
  if(IsPath(vv,x,y-1,n,m)){
    auto ret=RunMaze(vv,pos,x,y-1,n,m);
    if(ret){
      return true;
    }
  }
  if(IsPath(vv,x,y+1,n,m)){
    auto ret=RunMaze(vv,pos,x,y+1,n,m);
      if(ret){
        return true;
      }
  }
  pos.pop();
  return false;
}
int main()
{
  vector<vector<int>> vv;
  int n,m;
  cin>>n>>m;
  vv.resize(n);
  for(int i=0;i<n;++i){
    vv[i].resize(m);
    for(int j=0;j<m;++j){
      int val=0;
      cin>>val;
      vv[i][j]=val;
  }
  }
  auto ret=true;
  stack<pair<int,int>> pos;
  ret=RunMaze(vv,pos,0,0,n,m);
  //cout<<"RunMaze: "<<ret<<endl;
  if(ret){
    stack<pair<int,int>> revPos;
      while(!pos.empty()){
        revPos.push(pos.top());
        pos.pop();
      }
      while(!revPos.empty()){
      cout<<"("<<revPos.top().first<<","<<revPos.top().second<<")"<<endl;
      revPos.pop();
      }
  }
  return 0;
}

