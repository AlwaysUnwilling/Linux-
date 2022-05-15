#ifndef __TCPSERVER_HPP__
#define __TCPSERVER_HPP__ 

#include<iostream>
#include<unistd.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include"Log.hpp"


static const size_t BACKLOG=5;

class TcpServer
{
  private:
    int port;
    int listen_sock;
    static TcpServer* svr;
  private:
    TcpServer(int _port)
      :port(_port),listen_sock(-1)
    {}
  public:
    TcpServer(const TcpServer&)=delete;
    static TcpServer* GetInstance(int _port)
    {
      static pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
      if(svr==nullptr){
        pthread_mutex_lock(&lock);
        if(svr==nullptr){
          svr=new TcpServer(_port);
          svr->TcpServerInit();
        }
        pthread_mutex_unlock(&lock);
      }
      return svr;
    }
    void TcpServerInit()
    {
      Socket();
      Bind();
      Listen();
      LOG(INFO,"TcpServerInit ...success!");
    }
    void Socket()
    {
      this->listen_sock=socket(AF_INET,SOCK_STREAM,0);
      if(this->listen_sock<0)
      {
        LOG(FATAL,"socket error!");
        exit(1);
      }
      int opt=1;
      setsockopt(this->listen_sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
      LOG(INFO,"create socket ...success!");
    }
    void Bind()
    {
      struct sockaddr_in local;
      bzero(&local,0);
      local.sin_family=AF_INET;
      local.sin_port=htons(port);
      local.sin_addr.s_addr=INADDR_ANY;
      if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local))<0){
        LOG(FATAL,"bind error!");
        exit(2);
      }
      LOG(INFO,"bind socket ... success!");
    }
    void Listen()
    {
      if(listen(listen_sock,BACKLOG)<0){
        LOG(FATAL,"listen error!");
        exit(3);
      }
      LOG(INFO,"listen socket ...success!");
    }
    int GetSock()
    {
      return listen_sock;
    }
  ~TcpServer()
  {
    if(listen_sock>=0){
      close(listen_sock);
      listen_sock=-1;
    }
  }
};

TcpServer* TcpServer::svr=nullptr;
#endif 
