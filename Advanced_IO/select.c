#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/select.h>

int main(int argc,char* argv[])
{
    //通过对标准输入的监控，体会监控的嘴用
    while(1){
        //select(maxfd+1,可读事件集合，可写事件集合，异常事件集合，超时等待时间)；
        printf("Start monitoring\n");
        fd_set set;
        FD_ZERO(&set);//初始化清空集合
        FD_SET(0,&set);//将标准输入描述符添加到集合中
        struct timeval tv;
        tv.tv_sec=3;
        tv.tv_usec=0;
        int ret=select(0+1,&set,NULL,NULL,&tv);//1.select返回时会删除集合中没有继续的描述符
        if(ret<0){
            perror("select error\n");
            return -1;
        }else if(ret==0){
            printf("Monitoring timeout\n");
            continue;
        }
        printf("Descriptor ready or timeout waiting\n");
        if(FD_ISSET(0,&set)){
            //查看哪个描述符还在集合中，确定谁就绪了什么事件
            char buf[1024]={0};
            ret=read(0,buf,1023);
            if(ret<0){
                perror("read error\n");
                return -1;
            }
            printf("buf:%s\n",buf);
        }
    }
    return 0;
}
