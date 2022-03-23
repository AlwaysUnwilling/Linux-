#ifndef  __UDPSERVER_H__
#define  __UDPSERVER_H__ 

#include<iostream>
#include<string>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>


class udpServer 
{
  private:
    std::string ip;
    uint16_t port;
    int sock;
  private:
    static udpServer instant;
    udpServer()
      :ip("127.0.0.1"),port(8080),sock(-1)
    {}
  public:
    static udpServer* GetInstant()
    {
      return &instant;
    }
    udpServer(const udpServer&)=delete;
    void udpServerInit();
    void Start();
    
};



#endif 
