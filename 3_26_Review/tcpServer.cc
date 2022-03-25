#include"tcpServer.h"
#include<cstring>

tcpServer tcpServer::_instant;

void tcpServer::tcpServerInit()
{
  lsock=socket(AF_INET,SOCK_STREAM,0);
  if(lsock<0){
    std::cerr<<"socket error!"<<std::endl;
    exit(1);
  }
  struct sockaddr_in local;
  local.sin_family=AF_INET;
  local.sin_port=htons(port);
  local.sin_addr.s_addr=htonl(INADDR_ANY);
  if(bind(lsock,(struct sockaddr*)&local,sizeof(local))<0){
    std::cerr<<"bind error!"<<std::endl;
    exit(2);
  }
  if(listen(lsock,BACKLOG)<0){
    std::cerr<<"listen error!"<<std::endl;
    exit(3);
  }
  tp=ThreadPool::GetThreadObj();
  tp->ThreadPoolInit();
}

void tcpServer::Start()
{
  struct sockaddr_in peer;
  peer.sin_family=AF_INET;
  socklen_t len=sizeof(peer);
  while(true){
    int sock=accept(lsock,(struct sockaddr*)&peer,&len);
    if(sock<0){
      continue;
    }
    std::cout<<"IP/Port: "<<inet_ntoa(peer.sin_addr)<<":"<<ntohs(peer.sin_port)<<" linking now!"<<std::endl;
    Task* t=new Task(sock);
    tp->Put(t);
  }
}
