#include<iostream>
#include<signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include"tcpsocket.hpp"

#define CHECK_RET(q) if((q)==false){return -1;}

void sigcb(int signo)
{
    //SIGCHLD信号是一个非可靠信号，有可能丢失；
    //因此在一次信号处理中，就需要处理到没有子进程退出为止
    while(waitpid(-1,NULL,WNOHANG)>0);//返回值大于0，表示还有子进程要退出（非阻塞等待）
}
int main(int argc,char* argv[])
{
    //创建套接字
    if(argc!=3){
        std::cout<<"Usage:./tcp_srv ip port"<<std::endl;
        return -1;
    }
    signal(SIGCHLD,sigcb);
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
        pid_t pid=fork();
        if(pid==0){
            while(1){
                std::string buf;
                new_sock.Recv(&buf);
                std::cout<<"Client say: "<<buf<<std::endl;

                buf.clear();
                std::cout<<"Server say: ";
                std::cin>>buf;
                new_sock.Send(buf);
            } 
            new_sock.Close();
            exit(0);
        }
        new_sock.Close();//父进程关闭自己不适用的socket，不影响子进程的使用，父子进程数据独有
       // wait(NULL);
    }
    //关闭套接字
    lst_sock.Close();
    return 0;
}
