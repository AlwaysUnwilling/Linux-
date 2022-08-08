#ifndef __SOCK_HPP__
#define __SOCK_HPP__ 

#include<iostream>
#include<cstring>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

class Sock 
{
public:
  static int Socket()
  {
    int lsock=socket(AF_INET,SOCK_STREAM,0);
    if(lsock < 0){
      std::cerr<<"socket error!"<<std::endl;
      exit(1);
    }
    return lsock;
  }
  static void Bind(int lsock,int _port)
  {
    struct sockaddr_in local;
    memset(&local,0,sizeof(local));
    local.sin_family=AF_INET;
    local.sin_port=htons(_port);
    local.sin_addr.s_addr=INADDR_ANY;
    if(bind(lsock,(struct sockaddr*)&local,sizeof(local)) < 0){
      std::cerr<<"bind error!"<<std::endl;
      exit(2);
    }
  }
  static void Listen(int lsock,int backlen)
  {
    if(listen(lsock,backlen) < 0){
      std::cerr<<"listen error!"<<std::endl;
      exit(3);
    } 
  }
  static int Accept(int lsock)
  {
    struct sockaddr_in peer;
    peer.sin_family=AF_INET;
    socklen_t len=sizeof(peer);
    return accept(lsock,(struct sockaddr*)&peer,&len);
  }
  static bool Recv(int fd,std::string& out)
  {
    char ch=0;
    while(true){
      ssize_t rs=recv(fd,&ch,1,0);
      if(rs > 0){
        if(ch!='\n'){
          out+=ch;
        }else{
          break;
        }
      }else if(rs == 0){
        std::cout<<"client quit!"<<std::endl;
        return false;
      }else{
        std::cerr<<"recv error!"<<std::endl;
        return false;
      }
    }
    return true;
  }
  static bool Send(int fd,std::string& msg)
  {
    while(true){
      ssize_t ss=send(fd,msg.c_str(),msg.size(),0);
      if(ss < 0){
        std::cerr<<"send error!"<<std::endl;
        return false;
      }
    }
    return true;
  }
};
#endif 
