#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__ 

#include<iostream>
#include<string>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"ThreadPool.h"

#define BACKLOG 5

class tcpServer 
{
  private:
    int port;
    int lsock;
    ThreadPool* tp;
  private:
    tcpServer()
      :port(8080),lsock(-1),tp(nullptr)
    {}
    static tcpServer _instant;
  public:
    static tcpServer* GetInstant()
    {
      return &_instant;
    }
    tcpServer(const tcpServer&)=delete;
    void tcpServerInit();
    void Start();
    ~tcpServer()
    {
      if(!(lsock<0)){
        close(lsock);
      }
    }
};

#endif 
