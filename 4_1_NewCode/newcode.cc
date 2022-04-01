#include<iostream>
#include<vector>
//标题：另类加法:
//【另类加法】
//给定两个int A和B。编写一个函数返回A+B的值，但不得使用+或其他算数运算符。

class UnusualAdd {
  public:
    int addAB(int A, int B) {
      if(A==0){
        return B;
      }
      if(B==0){
        return A;
      }
      while(A!=0){
        int t=A^B;
        A=((A&B)<<1);
        B=t;
      }
      return B;
  }
};


//标题：走方格的方案数:
//【走方格的方案数】
//请计算n*m的棋盘格子（n为横向的格子数，m为竖向的格子数）从棋盘左上角出发沿着边缘线从左上角走到右下角，总共有多少种走法，要求不能走回头路，即：
//只能往右和往下走，不能往左和往上走。
//注：沿棋盘格之间的边缘线行走


int StepsNums(int n,int m)
{
  if(n==0 || m==0){
    return 1;
  }
  return StepsNums(n-1,m)+StepsNums(n,m-1);
}
int main()
{
  int n=0;
  int m=0;
  std::cin>>n>>m;
  std::cout<<StepsNums(n,m)<<std::endl;
  return 0;
}

