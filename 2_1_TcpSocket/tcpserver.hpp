#ifndef __TCPSERVER_HPP__
#define __TCPSERVER_HPP__

#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string>

#define NUM 5

class TcpServer
{
private:
    uint16_t _port;
    int _lsock;
public:
    TcpServer(uint16_t port=8080)
    :_port(port),_lsock(-1)
    {}
    void TcpServerInit()
    {
        _lsock=socket(AF_INET,SOCK_STREAM,0);
        if(_lsock<0){
            std::cerr<<"socket error!"<<std::endl;
            exit(1);
        }
        struct sockaddr_in local;
        local.sin_family=AF_INET;
        local.sin_port=htons(_port);
        local.sin_addr.s_addr=INADDR_ANY;
        socklen_t len=sizeof(local);
        if(bind(_lsock,(struct sockaddr*)&local,len)<0){
            std::cerr<<"bind error!"<<std::endl;
            exit(2);
        }
        if(listen(_lsock,NUM)<0){
            std::cerr<<"listen error!"<<std::endl;
            exit(3);
        }
    }
    void TcpServerStart()
    {
        struct sockaddr_in end_point;
        end_point.sin_family=AF_INET;
        socklen_t ep_len=sizeof(end_point);
        int _sock=accept(_lsock,(struct sockaddr*)&end_point,&ep_len);
        std::cout<<"End_Point IP:"<<inet_ntoa(end_point.sin_addr)<<" End_Point Port:"
            <<ntohs(end_point.sin_port)<<std::endl;
        while(true){
            char buf[1024];
            buf[0]=0;
            ssize_t s=recv(_sock,buf,1023,0);
            if(s<0){
                std::cerr<<"recv error!"<<std::endl;
                break;
            }else if(s==0){
                std::cout<<"Client Quit!"<<std::endl;
                close(_sock);
                _sock=-1;
            }else{
                buf[s]=0;
                std::string ans;
                ans+=buf;
                ans+=" [Server Echo]";
                send(_sock,ans.c_str(),ans.size(),0);
            }
        }
        close(_sock);
        _sock=-1;
    }
    ~TcpServer()
    {
        if(_lsock>0){
            close(_lsock);
            _lsock=-1;
        }
    }
};







#endif
