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
  dic.insert({"string","字符串"});
  dic.insert({"apple","苹果"});
  dic.insert({"banana","香蕉"});
  dic.insert({"orange","橘子"});
  dic.insert({"pear","梨"});
  dic.insert({"melon","西瓜"});
  dic.insert({"student","学生"});
  dic.insert({"teacher","老师"});
  dic.insert({"map","地图"});
}

void tcpServer::do_server(int fd)
{
  char request[1024]={0};
  while(true){
    ssize_t s=recv(fd,request,1023,0);
    if(s>0){
      request[s]=0;
      auto it=dic.find(request);
      if(it!=dic.end()){
        if(send(fd,it->second.c_str(),it->second.size(),0)<0){
          std::cerr<<"send error!"<<std::endl;
        }
      }else{
        if(send(fd,"Unknow word!",strlen("Unknow word!"),0)<0){
          std::cerr<<"send error!"<<std::endl;
        }
      }
    }else if(s==0){
      std::cout<<"Client quit!"<<std::endl;
      break;
    }else{
      std::cerr<<"recv error!"<<std::endl;
    }
  }
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
    do_server(sock);
  }
}
