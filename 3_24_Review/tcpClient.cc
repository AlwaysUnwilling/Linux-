#include"tcpClient.h"




void tcpClient::tcpClientInit()
{
  sock=socket(AF_INET,SOCK_STREAM,0);
  if(sock<0){
    std::cerr<<"socket error!"<<std::endl;
    exit(6);
  }
  struct sockaddr_in peer;
  peer.sin_family=AF_INET;
  peer.sin_port=htons(port);
  peer.sin_addr.s_addr=inet_addr(ip.c_str());
  if(connect(sock,(struct sockaddr*)&peer,sizeof(peer))<0){
    std::cerr<<"connect error!"<<std::endl;
    exit(7);
  } 
  std::cout<<"connect succeed!"<<std::endl;
}
void tcpClient::Start()
{
  std::string request;
  while(true){
    std::cout<<"[Enter Request: ]";
    fflush(stdout);
    std::getline(std::cin,request);
    if(send(sock,request.c_str(),request.size(),0)<0){
      std::cerr<<"send error!"<<std::endl;
      exit(8);
    }
    char response[1024]={0};
    ssize_t s=recv(sock,response,sizeof(response),0);
    if(s>0){
      response[s]=0;
      std::cout<<"[Sever Echo: ]"<<response<<std::endl;
    }else{
      std::cerr<<"recv error!"<<std::endl;
    }
  }
}
