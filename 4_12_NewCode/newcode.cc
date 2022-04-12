#include<iostream>
#include<vector>
#include<string>

using namespace std;

//标题：参数解析
/*
 【参数解析】
在命令行输入如下命令：
xcopy /s c:\\ d:\\e，
各个参数如下：
参数1：命令字xcopy
参数2：字符串/s 参数3：字符串c:\\
参数4: 字符串d:\\e 请编写一个参数解析程序，实现将命令行各个参数解析出来。
解析规则：
1.参数分隔符为空格
2.对于用""包含起来的参数，如果中间有空格，不能解析为多个参数。比如在命令行输入xcopy /s "C:\\program files" "d:\"时，参数仍然是4个，第3个参数应该是
字符串C:\\program files，而不是C:\\program，注意输出参数时，需要将""去掉，引号不存在嵌套情况。
3.参数不定长
4.输入由用例保证，不会出现不符合要求的输入
 * */
#include<iostream>
#include<string>
#include<vector>
void AnalyzeRecv(std::vector<std::string>& vs,std::string& recv)
{
  size_t end=0;
  while(end<recv.size()){
    if(recv[end]=='"'){
      end++;
      std::string str;
      while(end<recv.size() && recv[end]!='"'){
        str+=recv[end++];

      }
      vs.push_back(str);
    }else{
      while(end<recv.size() && recv[end]==' '){
        end++;

      }
      std::string str;
      while(end<recv.size() && recv[end]!=' '){
        str+=recv[end++];

      }
      vs.push_back(str);

    }
    end++;
  }
}
int main()
{
  std::string recv;
  std::getline(std::cin,recv);
  std::vector<std::string> vs;
  AnalyzeRecv(vs,recv);
  std::cout<<vs.size()<<std::endl;
  for(auto& e:vs){
    std::cout<<e<<std::endl;

  }
  return 0;
}

//标题：跳石板
/*
 【跳石板】小易来到了一条石板路前，每块石板上从1挨着编号为：1、2、3.......
这条石板路要根据特殊的规则才能前进：对于小易当前所在的编号为K的 石板，小易单次只能往前跳K的一个约数(不含1和K)步，即跳到K+X(X为K的一个非1和本身
的约数)的位置。 小易当前处在编号为N的石板，他想跳到编号恰好为M的石板去，小易想知道最少需要跳跃几次可以到达。
 * */

#include<limits.h>
#include<math.h>


void GetDivNum(int num,vector<int>& div)
{
  for(int i=2;i<=sqrt(num);++i){
    if(num%i==0){
      div.push_back(i);
    }
  }
}
int Jump(int n,int m)
{
  vector<int> step(m+1,INT_MAX);  //INT_MAX表示不可到达
  step[n]=0;  //当前位置初始化--即从当前位置跳到当前位置不需要花费步数
  for(int i=n;i<=m;++i){
    if(step[i]==INT_MAX){
      continue;
    }
    vector<int> div;
    GetDivNum(i,div);
    for(int j=0;j<div.size();++j){
      if(div[j]+i<=m && step[div[j]+i]!=INT_MAX){
        step[div[j]+i]=min(step[div[j]+i],step[i]+1);
      }else if(div[j]+i<=m){
        step[div[j]+i]=step[i]+1;
      }
    }
  }
  return step[m]==INT_MAX?-1:step[m];
}
int main()
{
  int n,m,minStep;
  while(cin>>n>>m){
    minStep=Jump(n,m);
    cout<<minStep<<endl;
  }
  return 0;
}

