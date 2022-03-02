#ifndef __SOCK_HPP__
#define __SOCK_HPP__

#include<iostream>
#include<cstring>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define BACKLOG 5

class Sock
{
public:
    static void Socket(int& lsock)
    {
        lsock=socket(AF_INET,SOCK_STREAM,0);
        if(lsock<0){
            std::cerr<<"Socket error!"<<std::endl;
            exit(1);
        }
    }
    static void Bind(int lsock,uint16_t port)
    {
        struct sockaddr_in local;
        local.sin_family=AF_INET;
        local.sin_port=htons(port);
        local.sin_addr.s_addr=htonl(INADDR_ANY);
        if(bind(lsock,(struct sockaddr*)&local,sizeof(local))<0){
            std::cerr<<"Bind error!"<<std::endl;
            exit(2);
        }
    }
    static void Listen(int lsock)
    {
        if(listen(lsock,BACKLOG)<0){
            std::cerr<<"Listen error!"<<std::endl;
            exit(3);
        }
    }
    static int Accept(int lsock)
    {
        struct sockaddr_in peer;
        bzero(&peer,sizeof(peer));
        socklen_t len=sizeof(peer);
        int sock=accept(lsock,(struct sockaddr*)&peer,&len);
        if(sock<0){
            std::cerr<<"Accept error"<<std::endl;
        }
        return sock;
    }
    static void SetSockOpt(int lsock)
    {
        int optval=1;
        setsockopt(lsock,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));
    }   
};




#endif
