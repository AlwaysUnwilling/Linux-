#include<iostream>
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
        std::string buf;
        new_sock.Recv(&buf);
        std::cout<<"Client say: "<<buf<<std::endl;

        buf.clear();
        std::cout<<"Server say: ";
        std::cin>>buf;
        new_sock.Send(buf);
    }
    //关闭套接字
    lst_sock.Close();
    return 0;
}
