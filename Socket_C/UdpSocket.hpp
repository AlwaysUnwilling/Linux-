#include<unistd.h>
#include<cstdio>
#include<string>
#include<sys/socket.h>//套接字接口信息
#include<netinet/in.h>//包含地址结构信息
#include<arpa/inet.h>//字节序转换接口


class UdpSocket
{
public:
    UdpSocket():_sockfd(-1)
    {}
    bool Socket()//创建套接字
    {
        //socket(地址域，套接字类型，协议类型)
        _sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
        if(_sockfd<0){
            perror("socket error!\n");
            return false;
        }
        return true;
    }
    bool Bind(const std::string &ip,uint16_t port)//为套接字绑定地址信息
    {
        //定义IPV4地址结构  struct sockaddr_in
        struct sockaddr_in addr;
        addr.sin_family=AF_INET;
        addr.sin_port=htons(port);//htons将主机字节序短整型数据转换为网络字节序数据
        addr.sin_addr.s_addr=inet_addr(ip.c_str());//将字符串IP地址转换为网络字节序
        //bind(描述符，地址信息，地址信息长度)
        socklen_t len=sizeof(struct sockaddr_in);
        int ret=bind(_sockfd,(struct sockaddr*)&addr,len);
        if(ret<0){
            perror("bind error!\n");
            return false;
        }
        return true;
    }
    bool Recv(std::string* buf,std::string* ip=NULL,uint16_t* port=NULL)//接收数据，获取发送端的地址信息
    {
        //recvfrom(套接字句柄，接收缓存区，数据长度，标识，源端地址，地址长度)
        struct sockaddr_in peer_addr;
        socklen_t len=sizeof(struct sockaddr_in);
        char tmp[4096]={0};
        int ret=recvfrom(_sockfd,tmp,4096,0,(struct sockaddr*)&peer_addr,&len);
        if(ret<0){
            perror("recvfrom error!\n");
            return false;
        }
        buf->assign(tmp,ret);//assign从指定字符串中截取指定长度的数据放到buf中
        if(port!=NULL){
            *port=ntohs(peer_addr.sin_port);//网络字节序到主机字节序的转换
        }
        if(ip!=NULL){
            *ip=inet_ntoa(peer_addr.sin_addr);//网络字节序到字符串IP地址的转换
        }
        return true;
    }
    bool Send(const std::string &data,const std::string &ip,const uint16_t port)//发送数据
    {
        //sendto(套接字句柄，数据首地址，数据长度，标识，对端地址信息，地址信息长度)
        struct sockaddr_in addr;
        addr.sin_family=AF_INET;
        addr.sin_port=htons(port);
        addr.sin_addr.s_addr=inet_addr(ip.c_str());
        socklen_t len=sizeof(struct sockaddr_in);
        int ret=sendto(_sockfd,data.c_str(),data.size(),0,(struct sockaddr*)&addr,len);
        if(ret<0){
            perror("sendto error!\n");
            return false;
        }
        return true;
    }
    bool Close()//关闭套接字
    {
        if(_sockfd>0){
            close(_sockfd);
            _sockfd=-1;
        }
        return true;
    }
private:
    int _sockfd;
};
