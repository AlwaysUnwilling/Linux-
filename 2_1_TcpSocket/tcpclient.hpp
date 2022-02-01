#ifndef __TCPCLIENT_HPP__
#define __TCPCLIENT_HPP__

#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string>



class TcpClient
{
private:
    uint16_t _port;
    std::string _ip;
    int _sock;
public:
    TcpClient(uint16_t port=8080,std::string ip="127.0.0.1")
    :_port(port),_ip(ip),_sock(-1)
    {}
    void TcpClientInit()
    {
        _sock=socket(AF_INET,SOCK_STREAM,0);
        if(_sock<0){
            std::cerr<<"socket error!"<<std::endl;
            exit(1);
        }
        struct sockaddr_in server;
        server.sin_family=AF_INET;
        server.sin_port=htons(_port);
        server.sin_addr.s_addr=inet_addr(_ip.c_str());
        socklen_t len=sizeof(server);
        if(connect(_sock,(struct sockaddr*)&server,len)<0){
            std::cerr<<"connect error!"<<std::endl;
            exit(2);
        }
    }
    void TcpClientStart()
    {
        char buf[1024];
        while(true){
            buf[0]=0;
            std::cout<<"Please Enter Massage: ";
            fflush(stdout);
            ssize_t s=read(0,buf,1023);
            if(s==0){
                std::cout<<"read NONE!"<<std::endl;
            }else if(s<0){
                std::cout<<"read error!"<<std::endl;
            }else{
                buf[s-1]=0;      //delete '\n'
                if(buf=="quit Y"){
                    break;
                }
                if(send(_sock,buf,sizeof(buf)-1,0)<0){
                    std::cerr<<"send error!"<<std::endl;
                }
            }
            char recvbuf[1024];
            recvbuf[0]=0;
            ssize_t ss=recv(_sock,recvbuf,1023,0);
            if(ss>0){
                recvbuf[ss]=0;
                std::cout<<recvbuf<<std::endl;
            }
        }
    }
    ~TcpClient()
    {
        if(_sock>=0){
            close(_sock);
            _sock=-1;
        }
    }
};








#endif
