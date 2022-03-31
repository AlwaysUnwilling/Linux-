//标题：求最小公倍数:
//【求最小公倍数】
//正整数A和正整数B 的最小公倍数是指 能被A和B整除的最小的正整数值，设计一个算法，求输入A和B的最小公倍数。

#include<iostream>
int GetGreatComMmultiple(int A,int B)
{
  int max=A;
  int min=B;
  if(A<B){
  max=B;
  min=A;
  }
  while(max%min){
  int tmp=max%min;
  max=min;
  min=tmp;
  }
  return min;
}
int GetLCM(int A,int B)
{
  int common=GetGreatComMmultiple(A,B);
  return A*B/common;
}
int main()
{
  int A=0;
  int B=0;
  std::cin>>A>>B;
  std::cout<<GetLCM(A,B)<<std::endl;
  return 0;
}

