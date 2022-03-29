#include<iostream>
#include<vector>
#include<string>
using namespace std;


/*标题：把字符串转换成整数:
将一个字符串转换成一个整数，要求不能使用字符串转换整数的库函数。 数值为 0 或者字符串不是一个合法的数值则返回 0
注意：
①字符串中可能出现任意符号，出现除 +/- 以外符号时直接输出 0
②字符串中可能出现 +/-且仅可能出现在字符串首 位*/
class Solution {
  public:
    int StrToInt(string str) {
      if(str.size()==0){
        return 0;
      }
      int ret=0;
      int flag=1;
      for(size_t i=0;i<str.size();++i){
        if(str[i]=='-' || str[i]=='+'){
          if(str[i]=='-'){
            flag=-1;
          }
          continue;
        }
        if(str[i]<'0' || str[i]>'9'){
          return 0;
        }
        ret*=10;
        ret+=str[i]-'0';
      }
      return ret*=flag;
    }
};

