#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__ 

#include<iostream>
#include<map>
#include<string>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define BACKLOG 5

class tcpServer 
{
  private:
    int port;
    int lsock;
    std::map<std::string,std::string> dic;
  private:
    tcpServer()
      :port(8080),lsock(-1)
    {}
    static tcpServer _instant;
    void do_server(int fd);
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
