#ifndef __EPOLLSERVER_HPP__
#define __EPOLLSERVER_HPP__ 

#include"sock.hpp"
#include<sys/epoll.h>
#include<cstring>

class Bucket
{
  public:
    int pos;
    char buff[10];
    int fd;
    Bucket(int _sock)
      :pos(0),fd(_sock)
    {
      memset(buff,0,sizeof(buff));
    }

};



const size_t SIZE=64;
class epollServer 
{
  private:
    int port;
    int lsock;
    int epfd;
  private:
    static epollServer instant;
    epollServer(int _port=DFL_PORT)
      :port(_port),lsock(-1),epfd(-1)
    {}
  private:
    void AddSock2Epoll(int sock,uint32_t event)
    {
      struct epoll_event ev;
      ev.events=event;
      if(sock==lsock){
        ev.data.ptr=nullptr;
      }else{
        ev.data.ptr=new Bucket(sock);
      }
      epoll_ctl(epfd,EPOLL_CTL_ADD,sock,&ev);
    }
    void DelSockFromEpoll(int sock)
    {
      close(sock);
      epoll_ctl(epfd,EPOLL_CTL_DEL,sock,nullptr);
    }
    void HandlerEvents(struct epoll_event revs[],int num)
    {
      for(int i=0;i<num;++i){
        uint32_t ev=revs[i].events;
        if(ev&EPOLLIN){
          if(revs[i].data.ptr==nullptr){
            int sock=Sock::Accept(lsock);
            if(sock<0){
              continue;
            }
            AddSock2Epoll(sock,EPOLLIN);
          }else{
            Bucket* bp=(Bucket*)revs[i].data.ptr;
            ssize_t s=recv(bp->fd,bp->buff+bp->pos,sizeof(bp->buff)-bp->pos,0);
            if(s>0){
                bp->pos+=s;
                std::cout<<"Client# "<<bp->buff<<std::endl;
                if(bp->pos>=sizeof(bp->buff)){
                  struct epoll_event tmp;
                  tmp.events=EPOLLOUT;
                  tmp.data.ptr=bp;
                  epoll_ctl(epfd,EPOLL_CTL_MOD,bp->fd,&tmp);
                }
            }else if(s==0){
                std::cout<<"Client quit!"<<std::endl;
                DelSockFromEpoll(bp->fd);
                delete bp;
            }else{
                std::cerr<<"recv error"<<std::endl;
                DelSockFromEpoll(bp->fd);
            }
          }
        }else if(ev&EPOLLOUT){
          Bucket* bp=(Bucket*)revs[i].data.ptr;
          send(bp->fd,bp->buff,sizeof(bp->buff),0);
          DelSockFromEpoll(bp->fd);
          delete bp;
        }else{
          //other events;
        }
      }
    }
  public:
    static epollServer* GetInstant()
    {
      return &instant;
    }
    epollServer(const epollServer&)=delete ;
    void epollServerInit()
    {
      Sock::Socket(lsock);
      Sock::Setsockopt(lsock);
      Sock::Bind(port,lsock);
      Sock::Listen(lsock);
      epfd=epoll_create(256);
      if(epfd<0){
        std::cout<<"epoll_create error!"<<std::endl;
        exit(5);
      }
    }
    void start()
    {
      AddSock2Epoll(lsock,EPOLLIN);
      int timeout=-1;
      struct epoll_event revs[SIZE];
      while(true){
        int num=epoll_wait(epfd,revs,SIZE,timeout);
        switch(num)
        {
          case 0:
            std::cout<<"time out ..."<<std::endl;
            break;
          case -1:
            std::cerr<<"epoll_wait error"<<std::endl;
            break;
          default:
            HandlerEvents(revs,num);
            break;
        }
      }
    }
    ~epollServer()
    {
      close(lsock);
      close(epfd);
    }
};

epollServer epollServer::instant;


#endif 
