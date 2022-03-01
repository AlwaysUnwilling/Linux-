#ifndef __POLLSERVER_HPP__
#define __POLLSERVER_HPP__

#include"Sock.hpp"
#include<poll.h>

#define DFL_PORT 8080
#define MAX 1024

class PollServer
{
private:
    uint16_t _port;
    int lsock;
    struct pollfd npfds[MAX]; 
private:
    void DelPollfdSock(struct pollfd& pd)
    {
        if(pd.fd>=0){
            pd.fd=-1;
            pd.events=0;
            pd.revents=0;
        }
    }
    void AddSock2Npfds(int sock)
    {
        for(auto& e:npfds){
            if(e.fd<0){
                e.fd=sock;
                e.events=POLLIN;
                std::cout<<"add a fd to npfds..."<<std::endl;
                return ;
            }
        }
    }
public:
    PollServer(uint16_t port=DFL_PORT):_port(port),lsock(-1)
    {}
    void PollServerInit()
    {
        for(auto& e:npfds){
            e.fd=-1;
            e.events=0;
            e.revents=0;
        }
        Sock::Socket(lsock);
        Sock::SetSockOpt(lsock);
        Sock::Bind(lsock,_port);
        Sock::Listen(lsock);
        npfds[0].fd=lsock;
        npfds[0].events=POLLIN;
    }
    void Start()
    {
        while(true){
            std::cout<<"npfds[MAX]: ";
            for(auto e:npfds){
                if(e.fd>=0){
                    std::cout<<e.fd<<" ";
                }
            }
            std::cout<<std::endl;
            int poll_val=poll(npfds,MAX,1000);
            if(poll_val>0){
                for(auto& e:npfds){
                    if(e.fd>=0 && e.revents==POLLIN){
                        if(e.fd==lsock){
                            //link events
                            int sock=Sock::Accept(lsock);
                            if(sock>=0){
                                std::cout<<"get a new link..."<<std::endl;
                                AddSock2Npfds(sock);
                            }
                        }else{
                            //data fd events
                            char buf[1024]={0};
                            ssize_t recv_size=recv(e.fd,buf,1023,0);
                            if(recv_size>0){
                                buf[recv_size-1]=0;
                                std::cout<<"client #: "<<buf<<std::endl;
                            }else if(recv_size==0){
                                std::cout<<"client quit..."<<std::endl;
                                close(e.fd);
                                DelPollfdSock(e);
                            }else{
                                std::cerr<<"recv error!"<<std::endl;
                                close(e.fd);
                                DelPollfdSock(e);
                            }
                        }
                    }
                }
            }else if(poll_val==0){
                std::cout<<"time out..."<<std::endl;
            }else{
                std::cerr<<"poll error!"<<std::endl;
            }
        }
    }
    ~PollServer()
    {
        if(lsock>=0){
            close(lsock);
            lsock=-1;
        }
    }
};




#endif
