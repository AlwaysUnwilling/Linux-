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
  request_t rq;
  response_t rp;
  std::cout<<"Enter x: ";
  std::cin>>rq.x;
  std::cout<<"Enter y: ";
  std::cin>>rq.y;
  std::cout<<"Enter op: ";
  std::cin>>rq.op;
  if(send(sock,&rq,sizeof(rq),0)<0){
    std::cerr<<"send error!"<<std::endl;
    exit(8);
  }
  ssize_t s=recv(sock,&rp,sizeof(rp),0);
  if(s>0){
    if(rp.code==0){
      std::cout<<"legal operation! Result: "<<rp.result<<std::endl;
    }else if(rp.code==1){
      std::cout<<"division by zero error!"<<std::endl;
    }else{
      std::cout<<"illegal operator!"<<std::endl;
    }
  }
}
