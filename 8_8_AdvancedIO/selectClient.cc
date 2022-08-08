#include"selectClient.h"


selectClient::selectClient(std::string _ip,int _port)
  :port(_port),ip(_ip),sock(-1)
{}
void selectClient::selectClientInit()
{
  sock=Sock::Socket();
  struct sockaddr_in peer;
  peer.sin_family=AF_INET;
  peer.sin_port=htons(port);
  peer.sin_addr.s_addr=inet_addr(ip.c_str());
  if(connect(sock,(struct sockaddr*)&peer,sizeof(peer)) < 0){
    std::cerr<<"connect error!"<<std::endl;
    exit(5);
  }
}
void selectClient::Run()
{
  //char buff[1024]={0};
  std::string msg;
  while(true){
    std::cout<<"[Please Enter Msg]# ";
    fflush(stdout);
    std::getline(std::cin,msg);
    msg+='\n';
    ssize_t s=send(sock,msg.c_str(),msg.size(),0);
    if(s <= 0){
      std::cerr<<"send error!"<<std::endl;
      exit(7);
    }
    //ssize_t rs=recv(sock,buff,1023,0);
    //if(rs > 0){
    //  buff[rs-1]=0;
    //  std::cout<<buff<<std::endl;
    //}else if(rs==0){
    //  std::cout<<"Server close!"<<std::endl;
    //  break;
    //}else{
    //  std::cerr<<"recv error!"<<std::endl;
    //  exit(8);
    //}
  }
}
selectClient::~selectClient()
{
  if(sock>=0){
    close(sock);
    sock=-1;
  }
}
