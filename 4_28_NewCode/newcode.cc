#include<iostream>


using namespace std;

//【跳台阶扩展问题】
/*
 *一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。求该青蛙跳上一个n级的台阶(n为正整数)总共有多少种跳法。
 * */

class Solution {
  public:
    int jumpFloorII(int number) {
      if(number==1){
        return number;
      }
      int ret=1;
      while(--number){
        ret*=2;
      }
      return ret;
    }
};


//【快到碗里来】
/*
 *】小喵们很喜欢把自己装进容器里的（例如碗），但是要是碗的周长比喵的身长还短，它们就进不去了。
现在告诉你它们的身长，和碗的半径，请判断一下能否到碗里去。
 * */

#include<string>
#include<stack>
#include<algorithm>
std::string AddString(std::string& s1,std::string& s2)
{
  if(s1.size()==0) return s2;
  if(s2.size()==0) return s1;
  int index1=s1.size()-1;
  int index2=s2.size()-1;
  int next=0;
  std::string ret;
  while(index1>=0 && index2>=0){
    int tmp=(s1[index1]-'0')+(s2[index2]-'0')+next;
    if(tmp>9){
      next=1;
      tmp-=10;
    }else{
      next=0;
    }
    ret+=tmp+'0';
    --index1;
    --index2;
  }
  while(index1>=0){
    int tmp=next+(s1[index1--]-'0');
    if(tmp>9){
      next=1;
      tmp-=10;
    }else{
      next=0;
    }
    ret+=tmp+'0';
  }
  while(index2>=0){
    int tmp=next+(s2[index2--]-'0');
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
  std::reverse(ret.begin(),ret.end());
  return ret;
}
std::string IsCatInBowl(std::string& n,std::string& r)
{
  std::string str("628");
  int end=r.size()-1;
  std::stack<std::string> st;
  std::string circ;
  while(end>=0){
    int next=0;
    std::string mul;
    for(int i=2;i>=0;--i){
      int tmp=(str[i]-'0')*(r[end]-'0')+next;
      if(tmp>9){
        next=tmp/10;
        tmp%=10;
      }
      mul+=tmp+'0';
    }
    if(next!=0){
      mul+=next+'0';
    }
    std::reverse(mul.begin(),mul.end());
    int count=end;
    while(count<r.size()-1){
      mul+='0';
      count++;
    }
    st.push(mul);
    end--;
  }
  while(!st.empty()){
    circ=AddString(st.top(),circ);
    st.pop();
  }
  if(circ.size()==n.size()){
    return circ<n?"No":"Yes";
  }else{
    return circ.size()>n.size()?"Yes":"No";
  }
}
int main()
{
  std::string n,r;
  while(std::cin>>n>>r){
    n+="00";
    std::cout<<IsCatInBowl(n,r)<<std::endl;
  }
  return 0;
}
