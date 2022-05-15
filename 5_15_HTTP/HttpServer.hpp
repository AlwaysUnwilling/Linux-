#ifndef __HTTPSERVER_HPP__
#define __HTTPSERVER_HPP__ 

#include<iostream>
#include<strings.h>
#include"TcpServer.hpp"
#include"Protocol.hpp"
#include"Log.hpp"

static const size_t PORT=8080;
class HttpServer 
{
  private:
    int port;
    TcpServer* tcp_server;
    bool stop;  //run status
  public:
    HttpServer(int _port=PORT)
      :port(_port),tcp_server(nullptr),stop(false)
    {}
    void HttpServerInit()
    {
      tcp_server=TcpServer::GetInstance(port);
    }
    void Loop()
    {
      LOG(INFO,"Loop begin...");
      int listen_sock=tcp_server->GetSock();
      while(!stop){
        struct sockaddr_in peer;
        bzero(&peer,0);
        socklen_t len=sizeof(peer);
        int sock=accept(listen_sock,(struct sockaddr*)&peer,&len);
        if(sock<0){
          continue;
        }
        LOG(INFO,"Get a new link...");
        int* _sock=new int(sock);
        pthread_t tid;
        pthread_create(&tid,nullptr,Entrance::HandlerRequest,_sock);
        pthread_detach(tid);
      }
    }
    ~HttpServer()
    {
      
    }
};
#endif 
