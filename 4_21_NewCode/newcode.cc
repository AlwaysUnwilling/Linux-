#include<iostream>
#include<string>

using namespace std;

//【字符串反转】
/*
 *接受一个只包含小写字母的字符串，然后输出该字符串反转后的字符串。（字符串长度不超过1000）
 * */

void ReverseStr(std::string& str)
{
  int left=0,right=str.size()-1;
  while(left<right){
    char tmp=str[left];
    str[left]=str[right];
    str[right]=tmp;
    left++;
    right--;
  }
}
int main()
{
  std::string str;
  std::cin>>str;
  ReverseStr(str);
  std::cout<<str<<std::endl;
  return 0;
}

//【公共子串计算】
/*
 *给定两个只包含小写字母的字符串，计算两个字符串的最大公共子串的长度。
注：子串的定义指一个字符串删掉其部分前缀和后缀（也可以不删）后形成的字符串。
 * */

int MaxLengthStr1AndStr2(std::string& str1,std::string& str2)
{
  int str1size=str1.size();
  int str2size=str2.size();
  int end1=0;
  int maxLength=0;
  while(end1<str1size){
    int end2=0;
    while(end2<str2size){
      if(str1[end1]==str2[end2]){
        int len=0;
        int i=end1;
        int j=end2;
        while(i<str1size && j<str2size && str1[i]==str2[j]){
          len++;
          i++;
          j++;
        }
        if(len>maxLength){
          maxLength=len;
        }
      }
      end2++;
    }
    end1++;
  }
  return maxLength;
}
int main()
{
  std::string str1,str2;
  std::cin>>str1>>str2;
  std::cout<<MaxLengthStr1AndStr2(str1,str2)<<std::endl;
  return 0;
}
