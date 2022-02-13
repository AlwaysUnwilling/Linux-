#ifndef __TCPCLIENT_HPP__
#define __TCPCLIENT_HPP__

#include<iostream>
#include<string>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<cstring>


class TcpClient
{
private:
    std::string ip;
    uint16_t port;
    int sock;
public:
    TcpClient(std::string _ip="127.0.0.1",uint16_t _port=9000)
    :ip(_ip),port(_port),sock(-1)
    {}
    void TcpClientInit()
    {
        sock=socket(AF_INET,SOCK_STREAM,0);
        if(sock<0){
            std::cerr<<"socket error!"<<std::endl;
            exit(1);
        }
        struct sockaddr_in server;
        server.sin_family=AF_INET;
        server.sin_port=htons(port);
        server.sin_addr.s_addr=inet_addr(ip.c_str());
        if(connect(sock,(struct sockaddr*)&server,sizeof(server))<0){
            std::cerr<<"connect error!"<<std::endl;
            exit(2);
        }
    }
    void Start()
    {
        char buff[64];
        while(true){
            buff[0]=0;
            std::cout<<"Please enter massage# ";
            fflush(stdout);
            size_t rs=read(0,buff,63);
            if(rs<0){
                std::cerr<<"read error!"<<std::endl;
                exit(4);
            }
            buff[rs-1]=0;
            if(send(sock,buff,strlen(buff),0)<0){
                std::cerr<<"send error!"<<std::endl;
                exit(3);
            }
            char ret[1024];
            size_t s=recv(sock,ret,1023,0);
            if(s>0){
                ret[s]=0;
                std::cout<<"Server # "<<ret<<std::endl;
            }
        }
    }
    ~TcpClient()
    {
        if(sock>0){
            close(sock);
            sock=-1;
        }
    }
};







#endif
