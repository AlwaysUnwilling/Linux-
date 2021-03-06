#include<iostream>
#include<string>
#include"UdpSocket.hpp"

#define CHECK_RET(q)  if((q)==false){return false;}

int main(int argc,char* argv[])
{
    //argc 标识程序运行参数的个数
    // ./udp_srv 192.168.2.2  9000   三个参数
    if(argc!=3){
        std::cout<<"Usage: ./udp_srv ip port"<<std::endl;
        return -1;
    }
    std::cout<<argv[2]<<std::endl;
    uint16_t port=std::stoi(argv[2]);
    std::cout<<"Port: "<<port<<std::endl;
    std::string ip=argv[1];
    std::cout<<"ip: "<<argv[1]<<std::endl;
    UdpSocket srv_sock;
    //创建套接字
    CHECK_RET(srv_sock.Socket());
    //绑定地址信息
    CHECK_RET(srv_sock.Bind(ip,port));
    while(1){
         //接收数据
        std::string buf;
        std::string peer_ip;
        uint16_t peer_port;
        CHECK_RET(srv_sock.Recv(&buf,&peer_ip,&peer_port));//接收对端数据
        std::cout<<"buf: "<<buf<<std::endl;                       
        std::cout<<"peer_ip: "<<peer_ip<<std::endl;
        std::cout<<"peer_port: "<<peer_port<<std::endl;
        std::cout<< "client["<<peer_ip<<":"<<peer_port<<"] say: "<<buf<<std::endl;
        //发送数据
        buf.clear();//清空buf
        std::cout<<"server say: ";
        std::cin>>buf;
        CHECK_RET(srv_sock.Send(buf,peer_ip,peer_port));//回复对端数据
    }
    //关闭套接字
    srv_sock.Close();
    return 0;
}
