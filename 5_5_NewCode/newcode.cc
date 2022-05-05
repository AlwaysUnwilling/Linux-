#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

//标题：不用加减乘除做加法
/*
 *写一个函数，求两个整数之和，要求在函数体内不得使用+、-、*、/四则运算符号。
 * */

class Solution {
  public:
    int Add(int num1, int num2) {
      while(num1){
        int tmp=(num1&num2)<<1;
        num2^=num1;
        num1=tmp;
      }
      return num2;
    }
};

//标题：三角形
/*
 *【三角形】给定三条边，请你判断一下能不能组成一个三角形。
 * */

bool CompareString(const string& s1,const string& s2)
{
  if(s1.size()>s2.size()){
    return true;
  }else if(s1.size()<s2.size()){
    return false;
  }else{
    return s1>s2?true:false;
  }
}
string AddString(const string& s1,const string& s2)
{
  int end1=s1.size()-1;
  int end2=s2.size()-1;
  int next=0;
  string ret;
  while(end1>=0 && end2>=0){
    int tmp=(s1[end1--]-'0')+(s2[end2--]-'0')+next;
    if(tmp>9){
      next=1;
      tmp-=10;
    }else{
      next=0;
    }
    ret+=tmp+'0';
  }
  while(end1>=0){
    int tmp=s1[end1--]-'0'+next;
    if(tmp>9){
      next=1;
      tmp-=10;
    }else{
      next=0;
    }
    ret+=tmp+'0';
  }
  while(end2>=0){
    int tmp=s1[end2--]-'0'+next;
    if(tmp>9){
      next=1;
      tmp-=10;
    }else{
      next=0;
    }
    ret+=tmp+'0';
  }
  if(next!=0){
    ret+=next+'0';
  }
  reverse(ret.begin(),ret.end());
  return ret;
}
string CanBuildTriangle(const string& a,const string& b,const string& c)
{
  string sumAB=AddString(a,b);
  string sumBC=AddString(c,b);
  string sumAC=AddString(a,c);
  if(CompareString(sumAB,c) && CompareString(sumBC,a) && CompareString(sumAC,b)){
    return "Yes";
  }else{
    return "No";
  }
}
int main()
{
  string a,b,c;
  while(cin>>a>>b>>c){
    cout<<CanBuildTriangle(a,b,c)<<endl;
  }
  return 0;
}

