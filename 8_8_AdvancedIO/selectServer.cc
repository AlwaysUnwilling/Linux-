#include"selectServer.h"

selectServer* selectServer::refServer=nullptr;
pthread_mutex_t selectServer::lock=PTHREAD_MUTEX_INITIALIZER;
const int DEF_FD=-1;
const size_t NUM=1024;

selectServer::selectServer(int _port,int _backlen)
  :port(_port),backlen(_backlen),lsock(-1)
{}
void selectServer::selectServerInit()
{
  lsock=Sock::Socket();
  Sock::Bind(lsock,port);
  Sock::Listen(lsock,backlen);
  std::cout<<"selectServer init done ..."<<std::endl;
}
void selectServer::HandlerEvents(fd_set& rfds,std::vector<int>& fdArray)
{
  for(auto& fd:fdArray){
    if(fd==DEF_FD){
      continue;
    }
    if(FD_ISSET(fd,&rfds) > 0){
      if(fd==lsock){
        //link event 
        int sock=Sock::Accept(fd);
        if(sock >= 0){
          bool flag=false;
          for(auto& fd1:fdArray){
            if(fd1==DEF_FD){
              fd1=sock;
              flag=true;
              break;
            }
          }
          if(!flag){
            close(sock);  //fdArray is full
          }else{
            std::cout<<"get a new link..."<<std::endl;
          }
        }
      }else{
        //read event
        std::string out;
        if(Sock::Recv(fd,out)){
          std::cout<<"[Client ]# "<<out<<std::endl;
        }else{
          close(fd);
          fd=DEF_FD;    
        }
      }
    }
  }
}
void selectServer::Run()
{
  fd_set rfds;
  std::vector<int> fdArray(NUM,DEF_FD);  //用来初始化数据中的所有fd
  fdArray[0]=lsock;
  while(true){
   // std::cout<<"i am running..."<<std::endl;
   // sleep(1);
   struct timeval timeout={5,0}; //每隔5秒超时
   FD_ZERO(&rfds);
   int maxFds=DEF_FD;
   for(const auto& fd:fdArray){
     if(fd==DEF_FD){
       continue;
     }
     FD_SET(fd,&rfds);
     if(maxFds < fd){
      maxFds=fd; 
     }
   }
   switch(select(maxFds+1,&rfds,nullptr,nullptr,&timeout)){
    case 0:
      //等待超时
      std::cout<<"select time out!"<<std::endl;
      break;
    case -1:
      //select error
      std::cerr<<"select error!"<<std::endl;
      break;
    default:
      //正常处理事件
      //std::cout<<"events occurs..."<<std::endl;
      HandlerEvents(rfds,fdArray);
      break;
   }
  }
}
selectServer::~selectServer()
{
  if(lsock >= 0){
    close(lsock);
    lsock=-1;
  }
}
