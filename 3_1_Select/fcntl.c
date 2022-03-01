/*************************************************************************
	> File Name: fcntl.c
	> Author: 
	> Mail: 
	> Created Time: Tue 01 Mar 2022 01:20:47 PM CST
    > About:non-blocking wait：fcntl
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

void SetNonBlock(int fd)
{
    int fl=fcntl(fd,F_GETFL);        //获取文件状态标记  F_SETFL
    if(fl<0){
        perror("fcntl error!\n");
        return ;
    }
    fcntl(fd,F_SETFL,fl|O_NONBLOCK); //设置文件状态标记 F_SETFL   fl|O_NONBLOCK; 
}
int main()
{
    char ch=0;
    SetNonBlock(0);    //将标准输入设置为非阻塞状态
    while(1){
        sleep(1);
        ssize_t s=read(0,&ch,1);
        if(s>0){
            printf("ch=%c\n",ch);
        }else if(s<0 && errno==EAGAIN){   //如果读取的errno==EAGAIN 并不是读取错误而是读取条件没有就绪
            printf("errno:%d\n",errno);
            printf("read condition not ok!\n");
        }else{
            printf("read error!\n");
        }
        printf("............................\n");
    }
    return 0;
}
