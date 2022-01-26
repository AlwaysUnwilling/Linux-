#ifndef __UDPSERVER_H__
#define __UDPSERVER_H__

#include<iostream>
#include<string>
#include<cstring>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

class UdpServer
{
public:
    UdpServer(std::string ip="127.0.0.1",uint16_t port=8080)
    :_ip(ip)
    ,_port(port)
    ,_sock(-1)
    {}
    void UdpServerInit()
    {
        _sock=socket(AF_INET,SOCK_DGRAM,0);
        if(_sock<0){
            std::cerr<<"socket error!"<<std::endl;
            exit(1);
        }
        struct sockaddr_in local;
        local.sin_family=AF_INET;
        local.sin_port=htons(_port);
        local.sin_addr.s_addr=inet_addr(_ip.c_str());
        std::cout<<local.sin_addr.s_addr<<" # "<<local.sin_port<<std::endl;
        if(bind(_sock,(struct sockaddr*)&local,sizeof(local))<0){
            std::cerr<<"bind error!"<<std::endl;
            exit(2);
        }
        std::cout<<"_sock:"<<_sock<<std::endl;
    }
    void Start()
    {
        char buff[1024];
        while(true){
            buff[0]='\0';
            struct sockaddr_in end_point;
            socklen_t len=sizeof(end_point);
            ssize_t size=recvfrom(_sock,buff,sizeof(buff)-1,0,(struct sockaddr*)&end_point,&len);
            
            if(size>0){
                std::cout<<"recvfrom sucess!"<<std::endl;
                buff[size]='\0';
                std::cout<<"Received!"<<std::endl;
                std::cout<<"End_Point IP: "<<inet_ntoa(end_point.sin_addr)<<"End_Point Port: "<<
                    ntohs(end_point.sin_port)<<"# "<<buff<<std::endl;
                std::string ans;
                ans+=" #Server received.";
                sendto(_sock,ans.c_str(),ans.size(),0,(struct sockaddr*)&end_point,len);
            }
        }       
    }
    ~UdpServer()
    {
        close(_sock);
    }
private:
    std::string _ip;
    uint16_t _port;
    int _sock;
};











#endif
