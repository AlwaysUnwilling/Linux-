#include<iostream>
#include<vector>
#include<set>
#include<stack>

using namespace std;
/*Fibonacci数列:
【Fibonacci数列】Fibonacci数列是这样定义的：
F[0] = 0
F[1] = 1
for each i ≥ 2: F[i] = F[i-1] + F[i-2]
因此，Fibonacci数列就形如：0, 1, 1, 2, 3, 5, 8, 13, ...，在Fibonacci数列中的数我们称为Fibonacci数。给你一个N，你想让其变为一个Fibonacci数，每一步你可
以把当前数字X变为X-1或者X+1，现在给你一个数N求最少需要多少步可以变为Fibonacci数。*/

static bool IsFibNum(int N)
{
  std::set<int> Fib;
  int f0=0;
  int f1=1;
  int f2=0;
  while(f2<=1000000){
  f2=f0+f1;
  Fib.insert(f2);
  f0=f1;
  f1=f2;
  }
  if(Fib.find(N)!=Fib.end()){
  return true;
  }
  return false;
}
int GetMinStepOfFib(int N)
{
  int minStep=0;
  if(!IsFibNum(N)){
    int step=0;
    int tmp=N;
    while(!IsFibNum(tmp)){
    tmp++;
    step++;
    }
    minStep=step;
    step=0;
    tmp=N;
    while(!IsFibNum(tmp)){
    tmp--;
    step++;
    }
    if(minStep>step){
    minStep=step;
    }
  }
  return minStep;
}
int main()
{
  int N=0;
  std::cin>>N;
  std::cout<<GetMinStepOfFib(N)<<std::endl;
  return 0;
}




/* 
 * 合法括号序列判断:
 * 【合法括号序列判断】
给定一个字符串A和其长度n，请返回一个bool值代表它是否为一个合法的括号串（只能由括号组成）。
 * */

class Parenthesis {
public:
bool chkParenthesis(string A, int n) {
    if(n==0 || n==1){
      return false;
    }
    std::stack<char> st;
    if(A[0]!='('){
    return false;
    }
    st.push(A[0]);
    for(size_t i=1;i<n;++i){
      if(A[i]!='(' && A[i]!=')'){
        return false;
      }else if(A[i]=='('){
        st.push(A[i]);
      }else{
        if(!st.empty() && st.top()=='('){
          st.pop();
        }else{
          return false;
        }
      }
    }
    if(!st.empty()){
      return false;
    }
    return true;
  }
};
