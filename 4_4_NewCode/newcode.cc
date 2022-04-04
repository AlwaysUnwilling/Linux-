#include<iostream>
#include<cmath>


//标题：二进制插入:
//给定两个32位整数n和m，同时给定i和j，将m的二进制数位插入到n的二进制的第j到第i位,保证n的第j到第i位均为零，且m的二进制位数小于等于i-j+1，其中二进制的位数从0开始由低到高。

class BinInsert {
public:
  int binInsert(int n, int m, int j, int i) {
    // write code here
    return n^(m<<j);
  }
};


//标题：查找组成一个偶数最接近的两个素数:
//任意一个偶数（大于2）都可以由2个素数组成，组成偶数的2个素数有很多种情况，本题目要求输出组成指定偶数的两个素数差值最小的素数对。
//

bool IsPrimer(int num)
{
  int tmp=sqrt(num);
  for(size_t i=2;i<=tmp;++i){
    if(num%i==0){
      return false;
    }
  }
  return true;
}
void PrintPrimer(int n)
{
  int bigPri=n/2;
  int litPri=n/2;
  int min=0;
  while(bigPri<n && litPri>=2){
    if(IsPrimer(bigPri) && IsPrimer(litPri)){
      std::cout<<litPri<<"\n"<<bigPri<<std::endl;
      break;
    }
    bigPri++;
    litPri--;
  }
}
int main()
{
  int n=0;
  std::cin>>n;
  PrintPrimer(n);
  return 0;
}

