#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    //匿名管道只能用于具有亲缘关系的进程间通信，子进程复制父进程的方式获取操作句柄
    //注意：创建管道一定要放在创建子进程前
    int pipefd[2]={-1};//pipefd[0]--用于从管道读取数据  pipefd[1]--用于向管道写入数据
    int ret=pipe(pipefd);
    if(ret<0){
        perror("pipe error\n");
        return -1;
    }
    pid_t pid=fork();
    if(pid==0){
        //子进程从管道读取数据
        char buf[1024]={0};
        read(pipefd[0],buf,1023);//使用pipefd[0]从管道读取数据 
        printf("child:%s\n",buf);
    }else if(pid>0){
        //父进程向管道写入数据
        char *ptr="这俩天好冷~~\n";
        write(pipefd[1],ptr,strlen(ptr));//使用pipefd[1]向管道写入数据
    }
    return 0;
}
