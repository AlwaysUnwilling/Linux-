#include<poll.h>
#include<unistd.h>
#include<stdio.h>

int main()
{
    struct pollfd poll_fd;//定义描述符的事件结构体数组（这里因为只监控一个描述符，因此定义了一个结构体）
    poll_fd.fd=0;//要监控的描述符
    poll_fd.events=POLLIN;//对于描述符要进行的事件--可读事件 
    for(;;){
        int ret=poll(&poll_fd,1,3000);//开始监控
        if(ret<0){//小于0表示出错
            perror("poll error\n");
            continue;
        }
        if(ret==0){//等于0表示超时
            printf("poll timeout\n");
            continue;
        }
        //revents不需要手动还原，因为下次监控时没有就绪就会自动置0
        if(poll_fd.revents==POLLIN){//调用返回后，通过每个节点的revents确定哪个描述符就绪了哪个事件
            char buf[1024]={0};//可读事件则进行读操作
            read(0,buf,sizeof(buf)-1);
            printf("stdin:%s",buf); 
            }else if(poll_fd.revents==POLLOUT){//可写事件进行写操作
                ;   
            }
    }
    return 0;
}
