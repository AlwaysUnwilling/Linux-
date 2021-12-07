#pragma once
#include<cstdio>
#include<string>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define MAX_LISTEN 5

class TcpSocket
{
public:
    TcpSocket():_sockfd(-1){}
    bool Socket()
    {
        //socket(地址域，套接字类型，协议类型)
        _sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        if(_sockfd<0){
            perror("Socket error!\n");
            return false;
        }
        return true;
    }
    int GetFd()
    {
        return _sockfd;
    }
    void SetFd(int fd)
    {
        _sockfd=fd;
    }
    bool Bind(const std::string& ip,uint16_t port)
    {
        struct sockaddr_in addr;
        addr.sin_family=AF_INET;
        addr.sin_port=htons(port);
        addr.sin_addr.s_addr=inet_addr(ip.c_str());
        socklen_t len=sizeof(struct sockaddr_in);
        int ret=bind(_sockfd,(struct sockaddr*)&addr,len);
        if(ret<0){
            perror("bind error!\n");
            return false;
        }
        return true;
    }
    bool Listen(int backlog=MAX_LISTEN)
    {
        //listen(套接字描述符，最大并发连接数)
        int ret=listen(_sockfd,backlog);
        if(ret<0){
            perror("listen error!\n");
            return false;
        }
        return true;
    }
    bool Accept(TcpSocket* new_sock,std::string* ip=NULL,uint16_t* port=NULL)
    {
        //新建套接字描述符=accept(监听套接字描述符，客户端地址信息，地址长度)
        struct sockaddr_in addr;
        socklen_t len=sizeof(addr);
        int new_fd=accept(_sockfd,(struct sockaddr*)&addr,&len);
        if(new_fd<0){
            perror("accept error!\n");
            return false;
        }
        new_sock->_sockfd=new_fd;
        if(ip!=NULL){
            *ip=inet_ntoa(addr.sin_addr);
        }
        if(port!=NULL){
            *port=ntohs(addr.sin_port);
        }
        return true;
    }
    bool Recv(std::string* buf)
    {
        //recv(通信套接字描述符，缓冲区首地址，接收数据长度，标志位)
        char tmp[4096]={0};
        int ret=recv(_sockfd,tmp,4096,0);
        if(ret<0){
            perror("recv error!\n");
            return false;
        }else if(ret==0){
            //recv默认阻塞，没有数据就会等待，返回0表示连接断开
            std::cout<<"connection broken!"<<std::endl;
            return false;
        }
        buf->assign(tmp,ret);
        return true;
    }
    bool Send(const std::string& data)
    {
        //send(描述符，要发送数据的首地址，要发送数据的长度，标志位)
        int ret=send(_sockfd,data.c_str(),data.size(),0);
        if(ret<0){
            perror("send error!\n");
            return false;
        }
        return true;
    }
    bool Close()
    {
        if(_sockfd>0){
            close(_sockfd);
            _sockfd=-1;
        }
        return true;
    }
    bool Connect(const std::string& ip,uint16_t port)
    {
        //向服务端发起连接
        //connect(描述符，服务端地址信息，地址信息长度)
        struct sockaddr_in addr;
        addr.sin_family=AF_INET;
        addr.sin_port=htons(port);
        addr.sin_addr.s_addr=inet_addr(ip.c_str());
        socklen_t len=sizeof(addr);
        int ret=connect(_sockfd,(struct sockaddr*)&addr,len);
        if(ret<0){
            perror("connect error!\n");
            return false;
        }
        return true;
    }
private:
    int _sockfd;
};
