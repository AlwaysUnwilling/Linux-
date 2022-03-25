#ifndef __TCP_CLIENT_H__
#define __TCP_CLIENT_H__ 

#include<iostream>
#include<map>
#include<string>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"protocol.hpp"

#define BACKLOG 5

class tcpClient 
{
  private:
    std::string ip;
    int port;
    int sock;
  private:
  public:
    tcpClient(std::string _ip,int _port)
      :ip(_ip),port(_port),sock(-1)
    {}
    void tcpClientInit();
    void Start();
    ~tcpClient()
    {
      if(!(sock<0)){
        close(sock);
      }
    }
};

#endif 
