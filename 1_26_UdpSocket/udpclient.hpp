#ifndef __UDPCLIENT_H__
#define __UDPCLIENT_H__

#include<iostream>
#include<string>
#include<cstring>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

class UdpClient
{
public:
    UdpClient(std::string ip="127.0.0.1",uint16_t port=8080)
    :_ip(ip)
    ,_port(port)
    ,_sock(-1)
    {}
    void UdpClientInit()
    {
        _sock=socket(AF_INET,SOCK_DGRAM,0);
        if(_sock<0){
            std::cerr<<"socket error!"<<std::endl;
            exit(1);
        }
        std::cout<<"_sock:"<<_sock<<std::endl;
    }
    void Start()
    {
        std::string buff;
        struct sockaddr_in server;
        server.sin_family=AF_INET;
        server.sin_port=htons(_port);
        server.sin_addr.s_addr=inet_addr(_ip.c_str());
        std::cout<<_ip<<" # "<<_port<<std::endl;
        std::cout<<server.sin_addr.s_addr<<" # "<<server.sin_port<<std::endl;
        while(true){
            std::cout<<"Please Enter Masg # ";
            std::cin>>buff;
            if(buff=="quit"){
                break;
            }
            std::cout<<"buff "<<buff.size()<<" # "<<buff<<std::endl;
            /*if(sendto(_sock,buff.c_str(),buff.size(),0,(struct sockaddr*)&server,sizeof(struct sockaddr_in))<0){
                std::cout<<"sockaddr_in "<<sizeof(struct sockaddr_in)<<std::endl;
                std::cout<<"sendto error!"<<std::endl;
            }*/
            sendto(_sock,buff.c_str(),buff.size(),0,(struct sockaddr*)&server,sizeof(server));
            char masg[1024];
            ssize_t size=recvfrom(_sock,masg,1023,0,nullptr,nullptr);
            if(size>0){
                std::cout<<"run here!"<<std::endl;
                masg[size]='\0';
                std::cout<<"Server Echo # "<<masg<<std::endl;
            }
        }
    }
    ~UdpClient()
    {
        close(_sock);
    }
private:
    std::string _ip;
    uint16_t _port;
    int _sock;
};











#endif
