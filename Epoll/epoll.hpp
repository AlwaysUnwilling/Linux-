#include"tcp_pthread.hpp"
#include<vector>
#include<unistd.h>
#include<sys/epoll.h>

class Epoll
{
public:
    Epoll()
    {
       //epoll_create(size);size已经被忽略，大于0即可
        _epfd=epoll_create(1);
        if(_epfd<0){
            perror("epoll_create error\n");
            _exit(0);
        }
    }
    bool Add(TcpSocket& sock)
    {
        int fd=sock.GetFd();
        //定义一个描述对应的事件结构体 struct epoll_event
        struct epoll_event ev;
        ev.data.fd=fd;//fd描述符就绪后，返回这个结构体中的data.fd就是我们要操作的描述符
        ev.events=EPOLLIN;//表示监控可读事件--EPOLLIN(可读)/EPOLLOUT（可写）；EPOLLIN | EPOLLOUT--可读可写（组合方式）
        //epoll_ctl(epoll句柄，操作类型，监控的描述符，描述符对应事件结构体)
        int ret=epoll_ctl(_epfd,EPOLL_CTL_ADD,fd,&ev);
        if(ret<0){
            perror("EPOLL_CTL_ADD error\n");
            return false;
        }
        return true;
    }
    bool Del(TcpSocket& sock)
    {
        int fd=sock.GetFd();
        int ret=epoll_ctl(_epfd,EPOLL_CTL_DEL,fd,NULL);
        if(ret<0){
            perror("EPOLL_CTL_DEL error\n");
            return false;
        }
        return true;
    }
    bool Wait(std::vector<TcpSocket>* list,int timeout=3000)
    {
        //epoll_wait(句柄，接收就绪结构的数组，数组节点数量，超时事件);
        struct epoll_event evs[10];
        int ret=epoll_wait(_epfd,evs,10,timeout);
        if(ret<0){
            perror("epoll_wait error\n");
            return false;
        }else if(ret==0){
            //超时事件
            printf("epoll timeout\n");
            return false;
        }
        for(int i=0;i<ret;i++){
            if(evs[i].events & EPOLLIN){//判断是否就绪的是可读事件---这里不能使用等于号，因为有可能就绪了多个事件（他们都是标志位）
                TcpSocket sock;
                sock.SetFd(evs[i].data.fd);
                list->push_back(sock);
            }
            if(evs[i].events & EPOLLOUT){
                //可写事件
                printf("This is EPOLLOUT\n");
            }
        }
        return true;
    }
private:
   int _epfd;
};
