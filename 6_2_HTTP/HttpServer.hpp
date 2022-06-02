#ifndef __HTTPSERVER_HPP__
#define __HTTPSERVER_HPP__ 

#include<iostream>
#include<signal.h>
#include<strings.h>
#include"TcpServer.hpp"
#include"Log.hpp"
#include"Task.hpp"
#include"ThreadPool.hpp"

static const size_t PORT=8080;
class HttpServer 
{
  private:
    int port;
    TcpServer* tcp_server;
    ThreadPool* thread_pool;
    bool stop;  //run status
  public:
    HttpServer(int _port=PORT)
      :port(_port),tcp_server(nullptr),thread_pool(nullptr),stop(false)
    {}
    void HttpServerInit()
    {
      //如果发送失败，系统会向进程发送sigpipe信号，如果不处理则进程会直接崩溃
      //忽略此信号
      signal(SIGPIPE,SIG_IGN);
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

        /*int* _sock=new int(sock);
        pthread_t tid;
        pthread_create(&tid,nullptr,Entrance::HandlerRequest,_sock);
        pthread_detach(tid);*/

        //创建任务，连接线程池
        Task task(sock);
        ThreadPool::GetInstance()->PushTask(task);
      }
    }
    ~HttpServer()
    {}
};
#endif 
