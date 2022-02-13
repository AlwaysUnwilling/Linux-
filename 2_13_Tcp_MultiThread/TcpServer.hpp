#ifndef __TCPSERVER_HPP__
#define __TCPSERVER_HPP__

#include<iostream>
#include<string>
#include<sys/types.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define BACKLOG 5

class TcpServer
{
private:
    uint16_t port;
    int lscok;
private:
    static void* start_routine(void* psock)
    {
        pthread_detach(pthread_self());
        int sock=*((int*)psock);
        char buff[1024];
        while(true){
            size_t s=recv(sock,buff,1023,0);
            if(s>0){
                buff[s]=0;
                std::cout<<"Client # "<<buff<<std::endl;
                std::string ans;
                ans+=buff;
                ans+=" [Server Echo!]";
                if(send(sock,ans.c_str(),ans.size(),0)<0){
                    std::cerr<<"send error!"<<std::endl;
                    exit(4);
                }
            }else if(s==0){
                std::cout<<"Client quit!"<<std::endl;
                break;
            }else{
                std::cerr<<"recv error!"<<std::endl;
                exit(3);
            }
        }
        close(sock);
        return nullptr;
    }
public:
    TcpServer(uint16_t _port=9000)
    :port(_port),lscok(-1)
    {}
    void TcpServerInit()
    {
        lscok=socket(AF_INET,SOCK_STREAM,0);
        if(lscok<0){
            std::cerr<<"socket error!"<<std::endl;
            exit(1);
        }
        struct sockaddr_in server;
        server.sin_family=AF_INET;
        server.sin_port=htons(port);
        server.sin_addr.s_addr=INADDR_ANY;
        if(bind(lscok,(struct sockaddr*)&server,sizeof(server))<0){
            std::cerr<<"bind error!"<<std::endl;
            exit(2);
        }
        if(listen(lscok,BACKLOG)<0){
            std::cerr<<"listen error!"<<std::endl;
        }
    }
    void Start()
    {
        struct sockaddr_in peer;
        peer.sin_family=AF_INET;
        socklen_t len=sizeof(peer);
        while(true){
            int sock=accept(lscok,(struct sockaddr*)&peer,&len);
            if(sock<0){
                continue;
            }
            std::cout<<"A new connection linking!"<<std::endl;
            std::cout<<"IP # "<<inet_ntoa(peer.sin_addr)<<" : Port # "
                <<ntohs(peer.sin_port)<<std::endl;
            pthread_t id=0;
            pthread_create(&id,nullptr,start_routine,(void*)&sock);
        }
    }
    ~TcpServer()
    {
        if(lscok>0){
            close(lscok);
            lscok=-1;
        }
    }
};





#endif
