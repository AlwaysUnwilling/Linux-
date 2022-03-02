#ifndef __EPOLLSERVER_HPP__
#define __EPOLLSERVER_HPP__

#include"Sock.hpp"
#include<sys/epoll.h>

#define DFL_PORT 8080
#define SIZE 64

class Bucket
{
public:
    char buff[5];  //request
    int fd;
    int pos;
    Bucket(int sock):fd(sock),pos(0)
    {
        memset(buff,0,sizeof(buff));
    }
};

class EpollServer
{
private:
    uint16_t _port;
    int lsock;
    int epfd;
private:
    void DelFdFromEpoll(int sock)
    {
        epoll_ctl(epfd,EPOLL_CTL_DEL,sock,nullptr);
    }
    void AddEvent2Epoll(int sock,uint32_t event)
    {
        struct epoll_event ev;
        ev.events=event;
        //TODO
        if(sock==lsock){
            ev.data.ptr=nullptr;
        }else{
            ev.data.ptr=new Bucket(sock);
        }
        epoll_ctl(epfd,EPOLL_CTL_ADD,sock,&ev);
    }
    void HandlerEvents(struct epoll_event* revs,int num)
    {
        for(int i=0;i<num;++i){
            uint32_t ev=revs[i].events;
            if(ev&EPOLLIN){  
                //read
                if(revs[i].data.ptr){
                    //recv data
                    Bucket* bp=(Bucket*)revs[i].data.ptr;  //void*
                    ssize_t recv_size=recv(bp->fd,bp->buff+bp->pos,sizeof(bp->buff)-bp->pos,0);
                    if(recv_size>0){
                        bp->pos+=recv_size;
                        std::cout<<"client # :"<<bp->buff<<std::endl;
                        if(bp->pos>=sizeof(bp->buff)){
                            //send(bp->fd,bp->buff,sizeof(buff),0);//如果写事件不满足会阻塞，
                                                                   //应该把对的fd的事件由读事件
                                                                   //改为写事件即可
                            struct epoll_event tempEvent;
                            tempEvent.events=EPOLLOUT;
                            tempEvent.data.ptr=bp;
                            epoll_ctl(epfd,EPOLL_CTL_MOD,bp->fd,&tempEvent);
                        }
                    }else if(recv_size==0){
                        std::cout<<"client quit..."<<std::endl;
                        close(bp->fd);
                        DelFdFromEpoll(bp->fd);
                        delete bp;
                    }else{
                        std::cout<<"recv error"<<std::endl;
                        close(bp->fd);
                        DelFdFromEpoll(bp->fd);
                        delete bp;
                    }
                }else{
                    //lsock 
                    int sock=Sock::Accept(lsock);
                    if(sock>=0){
                        std::cout<<"get a new link..."<<std::endl;
                        AddEvent2Epoll(sock,EPOLLIN);
                    }
                }
            }else if(ev&EPOLLOUT){ 
                //write
                Bucket* bp=(Bucket*)revs[i].data.ptr;
                send(bp->fd,bp->buff,sizeof(bp->buff),0);
                //如果期望发送的大小比实际发送的大小大，那么也需要等待全部发送完(bp->pos>=sizeof(bp->buff),)
                //才能关闭bp->fd
                close(bp->fd);
                DelFdFromEpoll(bp->fd);
                delete bp;
            }else{
                //others events
            }
        }
    }
public:
    EpollServer(uint16_t port=DFL_PORT):_port(port),lsock(-1),epfd(-1)
    {}
    void EpollServerInit()
    {
        Sock::Socket(lsock);
        Sock::SetSockOpt(lsock);
        Sock::Bind(lsock,_port);
        Sock::Listen(lsock);
        epfd=epoll_create(256);
        if(epfd<0){
            std::cerr<<"epoll_create error!"<<std::endl;
            exit(5);
        }
        std::cout<<"listen sock :"<<lsock<<std::endl;
        std::cout<<"epoll fd :"<<epfd<<std::endl;
    }
    void Start()
    {
        AddEvent2Epoll(lsock,EPOLLIN);
        int timeout=-1;
        struct epoll_event revs[SIZE];
        while(true){
            int num=epoll_wait(epfd,revs,SIZE,timeout);
            switch(num){
                case 0:
                    std::cout<<"time out..."<<std::endl;
                    break;
                case -1:
                    std::cout<<"epoll_wait error..."<<std::endl;
                    break;
                default:
                    HandlerEvents(revs,num);
                    break;
            }
        }
    }
    ~EpollServer()
    {
        if(lsock>=0){
            close(lsock);
        }
        if(epfd>=0){
            close(epfd);
        }
        epfd=lsock=-1;
    }
};


#endif

