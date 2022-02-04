#ifndef __TCPSERVERMP_HPP__
#define __TCPSERVERMP_HPP__

#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<signal.h>

#define BACKLOG 5


class TcpServerMp
{
private:
    uint16_t port;
    int lsock;
private:
    static void sighandle(int signum)
    {
        int status=0;
        pid_t pid=waitpid(-1,&status,0);
        std::cout<<"Child Pro pid: "<<pid<<
            " Status Code: "<<status<<std::endl;
    }
public:
    TcpServerMp(uint16_t _port=9000)
    :port(_port),lsock(-1)
    {}
    void TcpServerMpInit()
    {
        lsock=socket(AF_INET,SOCK_STREAM,0);
        if(lsock<0){
            std::cerr<<"sock: "<<lsock<<" socket() error!"<<std::endl;
            exit(1);
        }
        struct sockaddr_in server;
        server.sin_family=AF_INET;
        server.sin_port=htons(port);
        server.sin_addr.s_addr=INADDR_ANY;
        if(bind(lsock,(struct sockaddr*)&server,sizeof(server))<0){
            std::cerr<<"bind error!"<<std::endl;
            exit(2);
        }
        if(listen(lsock,BACKLOG)<0){
            std::cerr<<"listen error!"<<std::endl;
            exit(3);
        }
    }
    void Start()
    {
        signal(SIGCHLD,sighandle);
        struct sockaddr_in client;
        client.sin_family=AF_INET;
        socklen_t len=sizeof(client);
        while(true){
            int sock=accept(lsock,(struct sockaddr*)&client,&len);
            if(sock<0){
                continue;
            }
            pid_t pid=fork();
            if(pid==0){
                close(lsock);
                std::cout<<"Connection is successful!"<<std::endl;
                std::cout<<"cli IP: "<<inet_ntoa(client.sin_addr)
                    <<": PORT # "<<ntohs(client.sin_port)<<std::endl;
                char cliMsg[1024];
                cliMsg[0]=0;
                while(true){
                    ssize_t recvNum=recv(sock,cliMsg,1023,0);
                    if(recvNum>0){
                        cliMsg[recvNum]=0;
                        std::cout<<"Client: "<<cliMsg<<std::endl;
                        if(send(sock,"Server Received!",16,0)<0){
                            std::cout<<"server send error!"<<std::endl;
                        }
                    }else if(recvNum==0){
                        std::cout<<"client quit!"<<std::endl;
                        exit(0);
                    }else{
                        std::cout<<"recv error!"<<std::endl;
                        exit(3);
                    }
                }
            }
            if(pid<0){
                std::cout<<"fork error!"<<std::endl;
                exit(4);
            }
            close(sock);    
        }
    }
    ~TcpServerMp()
    {
        if(lsock>=0){
            close(lsock);
            lsock=-1;
        }
    }
};








#endif
