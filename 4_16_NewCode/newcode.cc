#include<iostream>
#include<vector>

using namespace std;

//标题：查找输入整数二进制中1的个数
/*
 【查找输入整数二进制中1的个数】
输入一个正整数，计算它在二进制下的1的个数。

 * */

int GetNumsOf1(int n)
{
  int count=0;
  while(n){
    count++;
    n=n&(n-1);
  }
  return count;
}
int main()
{
  int n=0;
  while(cin>>n){
    std::cout<<GetNumsOf1(n)<<std::endl;
  }
  return 0;
}

//【手套】
/*
 在地下室里放着n种颜色的手套，手套分左右手，但是每种颜色的左右手手套个数不一定相同。A先生现在要出门，所以他要去地下室选手套。但是昏暗的灯光让他
无法分辨手套的颜色，只能分辨出左右手。所以他会多拿一些手套，然后选出一双颜色相同的左右手手套。现在的问题是，他至少要拿多少只手套(左手加右手)，才
能保证一定能选出一双颜色相同的手套。
给定颜色种数n(1≤n≤13),同时给定两个长度为n的数组left,right,分别代表每种颜色左右手手套的数量。数据保证左右的手套总数均不超过26，且一定存在至少一种
合法方案。
 * */

class Gloves {
public:
  int findMinimum(int n, vector<int> left, vector<int> right) {
    int left_sum=0;
    int left_min=0;
    int right_sum=0;
    int right_min=0;
    int sum=0;
    for(int i=0;i<n;++i){
      if(left[i]*right[i]==0){
        sum+=left[i]+right[i];
      }else{
        left_sum+=left[i];
        left_min=left_min>left[i]?left[i]:left_min;

        right_sum+=right[i];
        right_min=right_min>right[i]?right[i]:right_min;
      }
    }
    return sum+min(left_sum-left_min+1,right_sum-right_min+1)+1;
  }
};
