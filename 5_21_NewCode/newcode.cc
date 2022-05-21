#include<iostream>
#include<vector>

//标题：发邮件
/*
 *【发邮件】NowCoder每天要给很多人发邮件。有一天他发现发错了邮件，把发给A的邮件发给了B，把发给B的邮件发给了A。于是他就思考，要给n个人发邮件，
在每个人仅收到1封邮件的情况下，有多少种情况是所有人都收到了错误的邮件？
即没有人收到属于自己的邮件。

 * */

using namespace std;
int main()
{
  int n;
  vector<long long> v;
  while(cin>>n){
    v.clear();
    v.resize(n+1,0);
    v[1]=0;
    v[2]=1;
    for(int i=3;i<=n;++i){
      v[i]=(i-1)*(v[i-1]+v[i-2]);
    }
    cout<<v[n]<<endl;
  }
  return 0;
}

//标题：最长上升子序列
/*
 *【最长上升子序列】广场上站着一支队伍，她们是来自全国各地的扭秧歌代表队，现在有她们的身高数据，请你帮忙找出身高依次递增的子序列。 例如队伍的身高
数据是（1、7、3、5、9、4、8），其中依次递增的子序列有（1、7），（1、3、5、9），（1、3、4、8）等，其中最长的长度为4。

 * */

int MaxSubLength(vector<int>& v,int n)
{
  vector<int> dp(n,0);
  for(int i=0;i<n;++i){
    dp[i]=1;
    for(int j=0;j<i;++j){
      if(v[i]>v[j]){
        dp[i]=dp[j]+1>dp[i]?dp[j]+1:dp[i];
      }
    }
  }
  int max=0;
  for(auto& e:dp){
    if(e>max){
      max=e;
    }
  }
  return max;
}
int main()
{
  int n;
  vector<int> v;
  while(cin>>n){
    v.clear();
    v.resize(n);
    for(int i=0;i<n;++i){
      cin>>v[i];
    }
    cout<<MaxSubLength(v,n)<<endl;
  }
  return 0;
}


