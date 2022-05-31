#include<iostream>
#include<string>

using namespace std;

//1.复数乘法哔哩哔哩2020校园招聘
/*
 *输入两个表示复数的字符串，输出它们相乘的结果的字符串
复数字符串用a+bi表示(a, b 为整数, i为虚数单位，i^2= -1)
 * */

int stringtoInt(string s)
{
  int num=0;
  int flag=1;
  for(int i=0;i<s.size();++i){
    if(s[i]=='-'){
      flag=-1;
    }
    else if(s[i]>='0' && s[i]<='9'){
      num=num*10+(s[i]-'0');
    }
  }
  return num*flag;
}
int main()
{
  string s1,s2;
  while(cin>>s1>>s2){
    string s1First=s1.substr(0,s1.find('+'));
    string s2First=s2.substr(0,s2.find('+'));
    string s1Second=s1.substr(s1.find('+')+1);
    string s2Second=s2.substr(s2.find('+')+1);
    int s1F=stringtoInt(s1First);
    int s2F=stringtoInt(s2First);
    int s1s=stringtoInt(s1Second);
    int s2s=stringtoInt(s2Second);
    int F=s1F*s2F-s1s*s2s;
    int S=s1F*s2s-s1s*s2F;
    cout<<F<<"+"<<S<<"i"<<endl;
  }
  return 0;
}
