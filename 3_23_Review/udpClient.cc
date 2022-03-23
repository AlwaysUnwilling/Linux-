#include"udpClient.h"
#include<cstring>

udpClient udpClient::instant;

void udpClient::udpClientInit()
{
  sock=socket(AF_INET,SOCK_DGRAM,0);
  if(sock<0){
    std::cerr<<"socket error!"<<std::endl;
    exit(1);
  }
}
void udpClient::Start()
{
  struct sockaddr_in peer;
  peer.sin_family=AF_INET;
  peer.sin_port=htons(port);
  peer.sin_addr.s_addr=inet_addr(ip.c_str());
  socklen_t len=sizeof(peer);
  char buff[1024]={0};
  while(true)
  {
    std::cout<<"[Client# ]";
    fflush(stdout);
    ssize_t s=read(0,buff,sizeof(buff)-1);
    if(s>0){
      buff[s-1]=0;
      if(sendto(sock,buff,strlen(buff),0,(struct sockaddr*)&peer,len)<0){
        std::cerr<<"sendto error!"<<std::endl;
        exit(5);
      }
      char ser[1024]={0};
      ssize_t rs=recvfrom(sock,ser,1023,0,nullptr,nullptr);
      if(rs>0){
        ser[rs]=0;
        std::cout<<ser<<std::endl;
      }
    }else{
      std::cerr<<"read error!"<<std::endl;
      exit(6);
    }
  } 
}

