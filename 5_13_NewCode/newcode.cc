#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

//标题：剪花布条
/*
 *【剪花布条】一块花布条，里面有些图案，另有一块直接可用的小饰条，里面也有一些图案。对于给定的花布条和小饰条，计算一下能从花布条中尽可能剪出几块小
饰条来呢？
输入包含多组数据。
每组数据包含两个字符串s,t，分别是成对出现的花布条和小饰条，其布条都是用可见ASCII字符表示的，可见的ASCII字符有多少个，布条的花纹也有多少种花样。
花纹条和小饰条不会超过1000个字符长。
 * */

int GetNum(const string& s,const string& t)
{
  if(s.size()<t.size()){
    return 0;
  }
  int max=0;
  for(int i=0;i<s.size();++i){
    int count=0;
    int begin=i;
    size_t index=0;
    while(true){
      index=s.find(t,begin);
      if(index==string::npos){
        break;
      }else{
      count++;
      begin=index+t.size();
      }
    }
    if(max<count){
      max=count;
    }
  }
  return max;
}
int main()
{
  string s,t;
  while(cin>>s>>t){
    cout<<GetNum(s,t)<<endl;
  }
  return 0;
}

//标题：客似云来
/*
 *NowCoder开了一家早餐店，这家店的客人都有个奇怪的癖好：他们只要来这家店吃过一次早餐，就会每天都过来；并且，所有人在这家店吃了两天早
餐后，接下来每天都会带一位新朋友一起来品尝。
于是，这家店的客人从最初一个人发展成浩浩荡荡成百上千人：1、1、2、3、5……
现在，NowCoder想请你帮忙统计一下，某一段时间范围那他总共卖出多少份早餐（假设每位客人只吃一份早餐).
 * */

string AddString(const string& s1,const string& s2)
{
  if(s1.size()==0 || s2.size()==0){
    return s1.size()>s2.size()?s1:s2;
  }
  int end1=s1.size()-1;
  int end2=s2.size()-1;
  int next=0;
  string ret;
  while(end1>=0 && end2>=0){
    int tmp=next+(s1[end1--]-'0')+(s2[end2--]-'0');
    if(tmp>9){
      tmp-=10;
      next=1;
    }else{
      next=0;
    }
    ret+=tmp+'0';
  }
  while(end1>=0){
    int tmp=next+(s1[end1--]-'0');
    if(tmp>9){
      tmp-=10;
      next=1;
    }else{
      next=0;
    }
    ret+=tmp+'0';
  }
  while(end2>=0){
    int tmp=next+(s2[end2--]-'0');
    if(tmp>9){
      tmp-=10;
      next=1;
    }else{
      next=0;
    }
    ret+=tmp+'0';
  }
  if(next>0){
    ret+=next+'0';
  }
  reverse(ret.begin(),ret.end());
  return ret;
}
string GetFiboNum(const string& n)
{
  if(n=="1" || n=="2"){
    return "1";
  }
  string f1("1");
  string f2("1");
  string ret;
  for(int i=3;i<=atoi(n.c_str());++i){
    ret=AddString(f1,f2);
    f1=f2;
    f2=ret;
  }
  return ret;
}
string NumOfBreakFast(const string& begin,const string& end)
{
  string sum;
  for(int i=atoi(begin.c_str());i<=atoi(end.c_str());++i){
    string tmp=GetFiboNum(to_string(i));
    sum=AddString(sum,tmp);
  }
  return sum;
}
int main()
{
  string begin,end;
  while(cin>>begin>>end){
    cout<<NumOfBreakFast(begin,end)<<endl;
  }
  return 0;
}
