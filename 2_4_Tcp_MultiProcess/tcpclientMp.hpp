#ifndef __TCPCLIENTMP_HPP__
#define __TCPCLIENTMP_HPP__

#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


class TcpClientMp
{
private:
    std::string ip;
    uint16_t port;
    int sock;
public:
    TcpClientMp(std::string _ip="127.0.0.1",uint16_t _port=9000)
    :ip(_ip),port(_port),sock(-1)
    {}
    void TcpClientMpInit()
    {
        struct sockaddr_in peer;
        peer.sin_family=AF_INET;
        peer.sin_port=htons(port);
        peer.sin_addr.s_addr=inet_addr(ip.c_str());
        sock=socket(AF_INET,SOCK_STREAM,0);
        if(sock<0){
            std::cerr<<"socket error!"<<std::endl;
            exit(1);
        }
        if(connect(sock,(struct sockaddr*)&peer,sizeof(peer))<0){
            std::cerr<<"connect error!"<<std::endl;
            exit(2);
        }
    }
    void Start()
    {
        char buff[1024];
        while(true){   
            std::cout<<"Please Enter Massage: ";
            fflush(stdout);
            buff[0]=0;
            ssize_t s=read(0,buff,1023);
            if(s>0){
                buff[s-1]=0;
                if(buff=="quit"){
                    break;
                }
                if(send(sock,buff,s-1,0)<0){
                    std::cerr<<"send error!"<<std::endl;
                }
            }
            if(s<0){
                std::cerr<<"read error!"<<std::endl;
            }
            char serAns[1024];
            serAns[0]=0;
            ssize_t serNum=recv(sock,serAns,1023,0);
            if(serNum>0){
                serAns[serNum]=0;
                std::cout<<"[server#]:"<<serAns<<std::endl;
            }
            
        }
    }
    ~TcpClientMp()
    {
        if(sock>=0){
            close(sock);
            sock=-1;
        }
    }
};








#endif
