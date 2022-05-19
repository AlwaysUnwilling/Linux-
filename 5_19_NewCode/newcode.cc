#include<iostream>
#include<vector>
#include<cstdio>

using namespace std;

//蘑菇阵
/*
现在有两个好友A和B，住在一片长有蘑菇的由n＊m个方格组成的草地，A在(1,1),B在(n,m)。现在A想要拜访B，由于她只想去B的家，所以每次她只会走(i,j+1)或(i+1,j)这样的路线，在草地上有k个蘑菇种在格子里(多个蘑菇可能在同一方格),问：A如果每一步随机选择的话(若她在边界上，则只有一种选择)，那么她不碰到蘑菇走到B的家的概率是多少？
 * */

int main()
{
    int n,m,k;
    while(cin>>n>>m>>k){
        vector<vector<double>> v(n+1,vector<double>(m+1,0.0));
        v[1][1]=1.0;
        for(int i=0;i<k;++i){
            int x,y;
            cin>>x>>y;
            v[x][y]=2;
        }
        for(int i=1;i<n+1;++i){
            for(int j=1;j<m+1;++j){
                if(!(i==1&&j==1)){
                    if(v[i][j]==2){
                        v[i][j]=0;
                    }else{
                        v[i][j]=v[i-1][j]*(j==m?1.0:0.5)+v[i][j-1]*(i==n?1.0:0.5);
                    }
                }
            }
        }
        printf("%.2f\n",v[n][m]);
    }
    return 0;
}

//红与黑
/*
 *】有一间长方形的房子，地上铺了红色、黑色两种颜色的正方形瓷砖。你站在其中一块黑色的瓷砖上，只能向相邻的（上下左右四个方向）黑色瓷砖移动。
请写一个程序，计算你总共能够到达多少块黑色的瓷砖。
 * */

#include<iostream>
#include<string>
#include<vector>
using namespace std;
bool IsPath(vector<string>& v,int m,int n,int x,int y)
{
  if(x>=0 && x<m && y>=0 && y<n && (v[x][y]=='.'|| v[x][y]=='@')){
    return true;
  }else{
    return false;
  }
}
void GetBlackNum(vector<string>& v,int& ret,int m,int n,int i,int j)
{
  if(v[i][j]=='.'){
    ret++;
    v[i][j]='@';
  }else if(v[i][j]=='@'){
    v[i][j]='#';
  }
  //上 (i-1,j)
  if(IsPath(v,m,n,i-1,j)){
    GetBlackNum(v,ret,m,n,i-1,j);
  }
  //下 (i+1,j)
  if(IsPath(v,m,n,i+1,j)){
    GetBlackNum(v,ret,m,n,i+1,j);
  }
  //左(i,j-1)
  if(IsPath(v,m,n,i,j-1)){
    GetBlackNum(v,ret,m,n,i,j-1);
  }
  //右(i,j+1)
  if(IsPath(v,m,n,i,j+1)){
    GetBlackNum(v,ret,m,n,i,j+1);
  }
}
int main()
{
  int m;
  int n;
  string str;
  vector<string> v;
  while(cin>>m>>n){
    v.clear();
    getchar();
    int k=0;
    int j=0;
    for(int i=0;i<m;++i){
      getline(cin,str);
      int pos=str.find('@');
      if(pos!=string::npos){
        j=pos;
        k=i;
      }
      v.push_back(str);
    }
    int ret=1;
    GetBlackNum(v,ret,m,n,k,j);
    cout<<ret<<endl;
  }
  return 0;
}
