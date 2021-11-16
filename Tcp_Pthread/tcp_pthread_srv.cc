#include<iostream>
#include<pthread.h>
#include"tcp_pthread.hpp"

#define CHECK_RET(q) if((q)==false){return -1;}


void* thr_worker(void* arg)
{
   /* TcpSocket* new_sock=(TcpSocket*)arg;
    std::string buf;
    new_sock->Recv(&buf);
    std::cout<<"Client say: "<<buf<<std::endl;

    buf.clear();
    std::cout<<"Server say: ";
    std::cin>>buf;
    new_sock->Send(buf);*/
    TcpSocket new_sock;
    long fd=(long)arg;
    new_sock.SetFd(fd);
    //通信
    while(1){
        std::string buf;
        new_sock.Recv(&buf);
        std::cout<<"Client say: "<<buf<<std::endl;

        buf.clear();
        std::cout<<"Server say: ";
        std::cin>>buf;
        new_sock.Send(buf);
    }
    new_sock.Close();//线程之间文件描述符表共享，这边关闭了其他地方就都用不了了
    return NULL;
}
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
        //TcpSocket* new_sock=new TcpSocket();
        bool ret=lst_sock.Accept(&new_sock);
        if(ret==false){
            continue;//服务端不能因为获取一个套接字失败就退出
        }
        pthread_t tid;
        //new_sock是一个局部对象，循环完毕时就会被释放，传地址会造成错误
        //除非每次accept的时候new_sock在堆上申请一个新的，不会自动释放，也要防止覆盖
        //或者直接传值--仅限于数据占用空间比较小的情况，数据太大可能会把栈占满
        int res=pthread_create(&tid,NULL,thr_worker,(void*)new_sock.GetFd());
        if(res!=0){
            perror("pthread error!\n");
            continue;
        }    
        pthread_detach(tid);//不关心线程返回值，也不向等待释放资源，因此将线程分离出去
        //new_sock.Close();//主线程不能关闭描述符，因为线程间贡献文件描述符表；与进程间不同
    }
    //关闭套接字
    lst_sock.Close();
    return 0;
}
