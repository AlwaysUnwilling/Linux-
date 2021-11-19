#include<iostream>
#include<sstream>
#include"tcpsocket.hpp"

#define CHECK_RET(q) if((q)==false){return -1;}

int main(int argc,char* argv[])
{
    //创建套接字
    if(argc!=3){
        std::cout<<"Usage:./tcp_srv ip port"<<std::endl;
        return -1;
    }
    std::string ip=argv[1];
    uint16_t port=std::stoi(argv[2]);
    TcpSocket lst_sock;
    CHECK_RET(lst_sock.Socket());
    //绑定地址信息
    CHECK_RET(lst_sock.Bind(ip,port));
    //开始监听
    CHECK_RET(lst_sock.Listen());
    //获取新连接
    while(1){
        //收发数据
        TcpSocket new_sock;
        bool ret=lst_sock.Accept(&new_sock);
        if(ret==false){
            continue;//服务端不能因为获取一个套接字失败就退出
        }
        std::string req;
        if(new_sock.Recv(&req)==false){
            new_sock.Close();
            continue;
        }
        std::cout<<"req:["<<req<<"]\n";
        std::string body="<html><body><h1>Hello World<h1></body></html>";
        std::stringstream header;
        header<<"Content-length: "<<body.size()<<"\r\n";
        header<<"Connection: close\r\n";
        std::string blank="\r\n";
        std::string first_line="HTTP/1.1 200 OK\r\n";
        new_sock.Send(first_line);
        new_sock.Send(header.str());
        new_sock.Send(blank);
        new_sock.Send(body);
        new_sock.Close();
    }
    //关闭套接字
    lst_sock.Close();
    return 0;
}
