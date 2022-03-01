#ifndef __SELECTSERVER_HPP__
#define __SELECTSERVER_HPP__

#include"Sock.hpp"

#define NUM (sizeof(fd_set)*8)
#define DFL_FD -1
class SelectServer
{
private:
    uint16_t _port;
    int lsock;
    int fd_array[NUM];
private:
    void DelFdArray(int index)
    {
        if(index>=0 && index<NUM){
            fd_array[index]=DFL_FD;
        }
    }
    void Add2Array(int sock)
    {
        int i=0;
        for(;i<NUM;i++){
            if(fd_array[i]==DFL_FD){
                break;
            }
        }
        if(i>=NUM){
            std::cerr<<"fd_array is full!close sock!"<<std::endl;
            close(sock);
        }else{
            fd_array[i]=sock;
            std::cout<<"fd: "<<sock<<"add to select.."<<std::endl;
        }
    }
    void HandlerEvents(fd_set* rfds)
    {
        for(int i=0;i<NUM;++i){
            if(fd_array[i]==DFL_FD){
                continue;
            }
            if(FD_ISSET(fd_array[i],rfds)){
                //read ready
                if(fd_array[i]==lsock){
                    //link event
                    int sock=Sock::Accept(lsock);
                    if(sock>=0){
                        //sock ok
                        std::cout<<"get a new link..."<<std::endl;
                        Add2Array(sock);
                    }
                }else{
                    //data ready event
                    char buf[1024];
                    buf[0]=0;
                    ssize_t recv_size=recv(fd_array[i],buf,1023,0);
                    if(recv_size>0){
                        buf[recv_size-1]=0;
                        std::cout<<"clent #: "<<buf<<std::endl;
                    }else if(recv_size==0){
                        std::cout<<"client quit!"<<std::endl;
                        close(fd_array[i]);
                        DelFdArray(i);
                    }else{
                        std::cout<<"recv error!"<<std::endl;
                        close(fd_array[i]);
                        DelFdArray(i);
                    }
                }
            }
        }
    }
public:
    SelectServer(uint16_t port=8080):_port(port),lsock(-1)
    {}
    void SelectServerInit()
    {
        for(int i=0;i<NUM;i++){
            fd_array[i]=DFL_FD;
        }
        lsock=Sock::Socket();
        Sock::Setsockopt(lsock);
        Sock::Bind(lsock,_port);
        Sock::Listen(lsock);
        fd_array[0]=lsock;
    }
    void Start()
    {
        int maxfd=DFL_FD;
        while(true){
            //select
            fd_set rfds;
            FD_ZERO(&rfds);//清空rfds
            std::cout<<"fd_array: ";
            for(int i=0;i<NUM;i++){
                if(fd_array[i]!=DFL_FD){
                    std::cout<<fd_array[i]<<" ";
                    FD_SET(fd_array[i],&rfds);//设置rfds
                    if(fd_array[i]>maxfd){
                        maxfd=fd_array[i]; 
                    }
                }
            }
            std::cout<<std::endl;
            std::cout<<"begin select..."<<std::endl;
            struct timeval timeout={5,0};//select()参数中timeout是输入输出型参数
                                        //每次输出后所有时间都会被重置为0；所以每次
                                        //循环都得重新设置
            switch(select(maxfd+1,&rfds,nullptr,nullptr,&timeout)){
                case 0:
                    std::cout<<"time out..."<<std::endl;
                    break;
                case -1:
                    std::cerr<<"select error!"<<std::endl; 
                    break;
                default:
                    //success
                    HandlerEvents(&rfds);
                    break;
            }
        }
    }
    ~SelectServer()
    {
        if(lsock>0){
            close(lsock);
            lsock=-1;
        }
    }
};




#endif
