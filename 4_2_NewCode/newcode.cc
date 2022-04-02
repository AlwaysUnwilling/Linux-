#include<iostream>
#include<string>


//标题：密码强度等级 |:
//【密码强度等级】密码按如下规则进行计分，并根据不同的得分为密码进行安全等级划分
//一、密码长度:
//5 分: 小于等于4 个字符
//10 分: 5 到7 字符
//25 分: 大于等于8 个字符
//二、字母:
/*0 分: 没有字母
10 分: 密码里的字母全都是小（大）写字母
20 分: 密码里的字母符合”大小写混合“
三、数字:
0 分: 没有数字
10 分: 1 个数字
20 分: 大于1 个数字
四、符号:
0 分: 没有符号
10 分: 1 个符号
25 分: 大于1 个符号
五、奖励（只能选符合最多的那一种奖励）:
2 分: 字母和数字
3 分: 字母、数字和符号
5 分: 大小写字母、数字和符号
最后的评分标准:
>= 90: 非常安全
>= 80: 安全（Secure）
>= 70: 非常强
>= 60: 强（Strong）
>= 50: 一般（Average）
>= 25: 弱（Weak）
>= 0: 非常弱（Very_Weak）
对应输出为：
VERY_SECURE
SECURE
VERY_STRONG
STRONG
AVERAGE
WEAK
VERY_WEAK
请根据输入的密码字符串，进行安全评定 */

#include<iostream>
#include<string>
std::string PassWdLevel(std::string& passwd)
{
  int point=0;
  int numSize=0;
  bool capLetter=false;
  bool lowLetter=false;
  int signSize=0;
  int size=passwd.size();
  if(size<=4){
    point+=5;
  }else if(size>=5 && size<=7){
    point+=10;
  }else{
    point+=25;
  }
  for(auto e:passwd){
    if(e>='a' && e<='z'){
      lowLetter=true;
    }else if(e>='0' && e<='9'){
      numSize++;
    }else if(e>='A' && e<='Z'){
      capLetter=true;
    }else{
      signSize++;
    }
  }
  if(numSize==0){
    point+=0;
  }else if(numSize==1){
    point+=10;
  }else{
    point+=20;
  }
  if(capLetter && lowLetter){
    point+=20;
  }else if(capLetter || lowLetter){
    point+=10;
  }else {
    point+=0;
  }
  if(signSize==0){
    point+=0;
  }else if(signSize==1){
    point+=10;
  }else{
    point+=25;
  }
  if(numSize!=0 && capLetter && lowLetter && signSize!=0){
    point+=5;
  }else if((capLetter || lowLetter) && numSize!=0 && signSize!=0){
    point+=3;
  }else if((capLetter || lowLetter) && numSize!=0){
    point+=2;
  }else{
    point+=0;
  }
  if(point>=90){
    return "VERY_SECURE";
  }else if(point>=80){
    return "SECURE";
  }else if(point>=70){
    return "VERY_STRONG";
  }else if(point>=60){
    return "STRONG";
  }else if(point>=50){
    return "AVERAGE";
  }else if(point>=25){
    return "WEAK";
  }else{
    return "VERY_WEAK";
  }
}
int main()
{
  std::string passwd;
  std::cin>>passwd;
  std::cout<<PassWdLevel(passwd)<<std::endl;
  return 0;
}
