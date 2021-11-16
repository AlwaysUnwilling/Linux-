#include<iostream>
#include"tcp_pthread.hpp"

#define CHECK_RET(q) if((q)==false) {return -1;}

int main(int argc,char* argv[])
{
    //创建套接字
    if(argc!=3){
        std::cout<<"Usage:./tcp_cli ip port"<<std::endl;
    }
    std::string srv_ip=argv[1];
    uint16_t srv_port=std::stoi(argv[2]);
    TcpSocket sock;
    CHECK_RET(sock.Socket());
    //绑定地址信息（不推荐）
    //向服务端发起连接请求
    CHECK_RET(sock.Connect(srv_ip,srv_port));
    while(1){
        //收发数据
        std::string buf;
        std::cout<<"Client say: ";
        std::cin>>buf;
        sock.Send(buf);

        buf.clear();
        sock.Recv(&buf);
        std::cout<<"Server say: "<<buf<<std::endl;
    }
    //关闭套接字
    sock.Close();
    return 0;
}
