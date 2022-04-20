#include<iostream>
#include<limits.h>
#include<string>

using namespace std;

//【汽水瓶】
/*
 *某商店规定：三个空汽水瓶可以换一瓶汽水，允许向老板借空汽水瓶（但是必须要归还）。
小张手上有n个空汽水瓶，她想知道自己最多可以喝到多少瓶汽水。
注意：本题存在多组输入。输入的 0 表示输入结束，并不用输出结果。
 * */

int GetMaxSoda(int n)
{
  if(n==1){
    return n;
  }
  if(n==2){
    return 3;
  }
  int max=0;
  int emptyBottle=n;
  while(emptyBottle>2){
    max+=emptyBottle/3;
    emptyBottle=emptyBottle/3+emptyBottle%3;
  }
  if(emptyBottle==2){
    return max+1;
  }else{
    return max;
  }
}
int main()
{
  int n=INT_MAX;
  while(std::cin>>n){
    if(n==0){
      break;
    }
    std::cout<<GetMaxSoda(n)<<std::endl;
  }
  return 0;
}

//【查找两个字符串a,b中的最长公共子串】
/*
 *查找两个字符串a,b中的最长公共子串。若有多个，输出在较短串中最先出现的那个。
注：子串的定义：将一个字符串删去前缀和后缀（也可以不删）形成的字符串。请和“子序列”的概念分开！
 * */
std::string GetSubString(std::string& a,std::string& b)
{
  int minlen=a.length();
  std::string minstr=a;
  int maxlen=b.length();
  std::string maxstr=b;
  if(minlen>maxlen){
    minlen=b.length();
    minstr=b;
    maxlen=a.length();
    maxstr=a;
  }
  std::string ret;
  int retlen=0;
  for(int i=0;i<minlen;)
  {
    int maxprev=0;
    int minprev=i;
    for(int j=0;j<maxlen;)
    {
      if(maxstr[j]==minstr[i]){
      maxprev=j;
      std::string tmp;
      int size=0;
      while(j<maxlen && i<minlen && maxstr[j]==minstr[i]){
        size++;
        tmp+=minstr[i];
        i++;
        j++;
      }
      if(retlen<size){
        retlen=size;
        ret=tmp;
      }
      j=maxprev+1;
      i=minprev;
      }else{
        ++j;
      }
    }
    i=minprev+1;
  }
  return ret;
}
int main()
{
  std::string a,b;
  std::cin>>a>>b;
  std::cout<<GetSubString(a,b)<<std::endl;
  return 0;
}
