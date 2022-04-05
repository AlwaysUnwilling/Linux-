#ifndef __SELECTSERVER_HPP__
#define __SELECTSERVER_HPP__ 

#include"sock.hpp"
#include<sys/select.h>

#define NUM (sizeof(fd_set)*8)
#define DFL_FD -1

class selectServer 
{
  private:
    int port;
    int lsock;
    int fd_array[NUM];
  private:
    static selectServer instant;
    selectServer(int _port=DFL_PORT)
      :port(_port),lsock(-1)
    {}
  private:
    void Add2Rdfs(int sock)
    {
      size_t i=0;
      for(;i<NUM;++i){
        if(fd_array[i]==DFL_FD){
          break;
        }
      }
      if(i>=NUM){
        std::cout<<"fd_array is full! close fd..."<<std::endl;
        close(sock);
      }else{
        fd_array[i]=sock;
      }
    }
    void HandlerEvents(fd_set* rdfs)
    {
      for(size_t i=0;i<NUM;++i){
        if(fd_array[i]==DFL_FD){
          continue;
        }
        if(FD_ISSET(fd_array[i],rdfs)){
          if(fd_array[i]==lsock){
            std::cout<<"get a new link..."<<std::endl;
            int sock=Sock::Accept(lsock);
            if(sock<0){
              continue;
            }
            std::cout<<"fd: "<<sock<<" add to select."<<std::endl;
            Add2Rdfs(sock);
          }else{
            //read ready.
            char buf[1024];
            ssize_t s=recv(fd_array[i],buf,sizeof(buf)-1,0);
            if(s>0){
              buf[s-1]=0;
              std::cout<<"client# "<<buf<<std::endl;
            }else if(s==0){
              std::cout<<"client quit"<<std::endl;
              close(fd_array[i]);
              fd_array[i]=DFL_FD;
            }else{
              std::cout<<"recv error!"<<std::endl;
              close(fd_array[i]);
              fd_array[i]=DFL_FD;
            }
          }
        }
      }
    }
  public:
    static selectServer* GetInstant()
    {
      return &instant;
    }
    selectServer(const selectServer&)=delete ;
    void selectServerInit()
    {
      for(size_t i=0;i<NUM;++i){
        fd_array[i]=DFL_FD;
      }
      Sock::Socket(lsock);
      Sock::Setsockopt(lsock);
      Sock::Bind(port,lsock);
      Sock::Listen(lsock);
      fd_array[0]=lsock;
    }
    void Start()
    {
      int maxfd=DFL_FD;
      fd_set rdfs;
      while(true){
        FD_ZERO(&rdfs);
        for(size_t i=0;i<NUM;++i){
          if(fd_array[i]!=DFL_FD){
            FD_SET(fd_array[i],&rdfs);
            if(maxfd<fd_array[i]){
              maxfd=fd_array[i];
            }
          }
        }
        std::cout<<"rdfs: ";
        for(auto e:fd_array){
          if(e!=DFL_FD){
            std::cout<<e<<" ";
          }
        }
        std::cout<<std::endl;
        switch(select(maxfd+1,&rdfs,nullptr,nullptr,nullptr))
        {
          case 0:
            std::cout<<"time out....."<<std::endl;
            break;
          case -1:
            std::cerr<<"select error!"<<std::endl;
            break;
          default:
            HandlerEvents(&rdfs);
            break;
        }
      }
    }
};

selectServer selectServer::instant;


#endif 
