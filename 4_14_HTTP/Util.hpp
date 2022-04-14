#pragma once 

#include<iostream>
#include<string> 
#include<sys/types.h>
#include<sys/socket.h>

// 工具类
class Util
{
  public:
    static int ReadLine(int sock,std::string& out)
    {
      char ch='x';
      while(ch!='\n'){
        ssize_t s=recv(sock,&ch,1,0);
        if(s>0){
          if(ch=='\r'){
          //'\r\n' '\r'
            recv(sock,&ch,1,MSG_PEEK); //窥探'\r'下一个字符;只查看不取走
            if(ch=='\n'){
              recv(sock,&ch,1,0);
            }else{
              ch='\n';             //将'\r'替换成'\n'
            }
          }
          //1.普通字符
          //2.'\n'
          out+=ch;
        }else if(s==0){
          return 0;
        }else{
          return -1;
        }
      }
      return out.size();
    }
};
