#ifndef  __UDPCLIENT_H__
#define  __UDPCLIENT_H__ 

#include<iostream>
#include<string>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>


class udpClient 
{
  private:
    std::string ip;
    uint16_t port;
    int sock;
  private:
    static udpClient instant;
    udpClient()
      :ip("127.0.0.1"),port(8080),sock(-1)
    {}
  public:
    static udpClient* GetInstant()
    {
      return &instant;
    }
    udpClient(const udpClient&)=delete;
    void udpClientInit();
    void Start();
    
};



#endif 
