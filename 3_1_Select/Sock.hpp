#ifndef __SOCK_HPP__
#define __SOCK_HPP__

#include<iostream>
#include<string>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<cstring>

#define BACKLOG 5

class Sock
{
public:
    static int Socket()
    {
        int lsock=socket(AF_INET,SOCK_STREAM,0);
        if(lsock<0){
            std::cerr<<"socket error!"<<std::endl;
            exit(2);
        }
        return lsock;
    }
    static void Bind(int lsock,int port)
    {
        struct sockaddr_in server;
        server.sin_family=AF_INET;
        server.sin_port=htons(port);
        server.sin_addr.s_addr=htonl(INADDR_ANY);
        if(bind(lsock,(struct sockaddr*)&server,sizeof(server))<0){
            std::cerr<<"bind error!"<<std::endl;
            exit(3);
        }
    }
    static void Listen(int lsock)
    {
        if(listen(lsock,BACKLOG)<0){
            std::cerr<<"listen error!"<<std::endl;
            exit(4);
        }
    }
    static int Accept(int lsock)
    {
        struct sockaddr_in peer;
        bzero(&peer,sizeof(peer));
        socklen_t len=sizeof(peer);
        int sock=accept(lsock,(struct sockaddr*)&peer,&len);
        if(sock<0){
            std::cerr<<"accept error!"<<std::endl;
        }
        return sock;
    }   
    static void Setsockopt(int lsock) //端口复用：防止断开连接时进入time_wait，导致服务器无法重启
    {
       int optval=1;
       setsockopt(lsock,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));
    }
};

#endif
