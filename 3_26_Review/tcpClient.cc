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
  char request[1024]={0};
  char response[1024]={0};
  std::cout<<"[Enter request: ]";
  fflush(stdout);
  ssize_t s=read(0,request,sizeof(request)-1);
  if(s>0){
    request[s-1]=0;
    if(send(sock,request,sizeof(request),0)<0){
      std::cout<<"send error!"<<std::endl;
    }
    ssize_t rs=recv(sock,response,sizeof(response)-1,0);
    if(rs>0){
      std::cout<<response<<std::endl;
    }
  }else if(s==0){
    std::cout<<"The service has been shut down by the remote!"<<std::endl;
  }else{
    std::cerr<<"read error!"<<std::endl;
  }
  close(sock);
}
