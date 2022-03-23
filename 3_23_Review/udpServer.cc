#include"udpServer.h"

udpServer udpServer::instant;

void udpServer::udpServerInit()
{
  sock=socket(AF_INET,SOCK_DGRAM,0);
  if(sock<0){
    std::cerr<<"socket error!"<<std::endl;
    exit(1);
  }
  struct sockaddr_in server;
  server.sin_family=AF_INET;
  server.sin_port=htons(port);
  server.sin_addr.s_addr=inet_addr(ip.c_str());
  if(bind(sock,(struct sockaddr*)&server,sizeof(server))<0){
    std::cerr<<"bind error!"<<std::endl;
    exit(2);
  }
}
void udpServer::Start()
{
  struct sockaddr_in peer;
  peer.sin_family=AF_INET;
  socklen_t len=sizeof(peer);
  char buff[1024]={0};
  while(true)
  {
    ssize_t s=recvfrom(sock,buff,sizeof(buff)-1,0,(struct sockaddr*)&peer,&len);
    if(s>0){
      buff[s]=0;
      std::cout<<"IP:"<<inet_ntoa(peer.sin_addr)<<"Port:"<<ntohs(peer.sin_port)<<"[Client#] "<<buff<<std::endl;
      std::string echo("[Echo# ]");
      echo+=buff;
      if(sendto(sock,echo.c_str(),echo.size(),0,(struct sockaddr*)&peer,len)<0){
        std::cerr<<"sendto error!"<<std::endl;
        exit(3);
      }
    }else{
      std::cerr<<"recvfrom error!"<<std::endl;
      exit(4);
    }
  }
}

