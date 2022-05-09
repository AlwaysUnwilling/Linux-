#include<iostream>
#include<cmath>
#include<string>
#include<vector>


using namespace std;

//因子个数
/*
一个正整数可以分解成一个或多个数组的积。例如36=2*2*3*3，即包含2和3两个因子。NowCoder最近在研究因子个数的分布规律，现在给出一系列正整数，他希望你开发一个程序输出每个正整数的因子个数。
 * */

int main()
{
    int n;
    while(cin>>n){
        int count =0;
        for(int i=2;i<=sqrt(n);++i){
            if(n%i==0){
                //继续排除n/i中可能包含的i因子
                while(n%i==0){
                    n/=i;
                }
                count++;
            }
        }
        //如果循环结束，n的值不为1，那么此时的n也是一个因子
        if(n!=1){
            count++;
        }
        cout<<count<<endl;
    }
    return 0;
}

//最难的问题
/*
 *NowCoder生活在充满危险和阴谋的年代。为了生存，他首次发明了密码，用于军队的消息传递。假设你是军团中的一名军官，需要把发送来的消息
破译出来、并提
供给你的将军。
消息加密的办法是：对消息原文中的每个字母，分别用该字母之后的第5个字母替换（例如：消息原文中的每个字母A 都分别替换成字母F），其他字符不 变，并且
消息原文的所有字母都是大写的。密码中的字母与原文中的字母对应关系如下。
密码字母：A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
原文字母：V W X Y Z A B C D E F G H I J K L M N O P Q R S T U
 * */

vector<string> ShowMessage(string& str)
{
  static const char codeTable[]={'V','W','X','Y','Z','A','B','C','D','E','F','G','H','I',
                                  'J','K','L','M','N','O','P','Q','R','S','T','U'};
  vector<string> vs;
  int end=0;
  string tmp;
  while(end<str.size()){
    if(str[end]=='<'){
      vs.push_back(tmp);
      tmp.clear();
      end+=5;
      continue;
    }
    tmp+=str[end++];
  }
  if(tmp.size()){
  vs.push_back(tmp);
  }
  for(auto& v:vs){
    for(auto& e:v){
      if(e==' '){
        continue;
      }
      e=codeTable[e-'A'];
    }
  }
  return vs;
}
int main()
{
  string str;
  while(getline(cin,str)){
    vector<string> vs=ShowMessage(str);
    string ret;
    for(int i=0;i<vs.size();++i){
      ret+=vs[i];
      if(i<vs.size()-1){
        ret+="<br/>";
      }
    }
    cout<<ret<<endl;
  }
  cout<<endl;
  return 0;
}

