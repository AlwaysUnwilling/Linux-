#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>


int main()
{
    int pipefd[2]={-1};
    if(pipe(pipefd)<0){
        perror("pipe error\n");
        return -1;
    }
    pid_t ps_pid=fork();
    if(ps_pid==0){
        //ps子进程
        dup2(pipefd[1],1);//将标准输出重定向到管道写入端
        execlp("ps","ps","-ef",NULL);
        exit(0);
    }
    pid_t grep_pid=fork();
    if(grep_pid==0){
        //grep子进程
        close(pipefd[1]);//关闭所有写端ps进程一旦退出，所有的写端被关闭，grep读完数据后返回0
        dup2(pipefd[0],0);//将标准输入重定向到管道的读取端
        execlp("grep","grep","ssh",NULL);
        exit(0);
    }
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(ps_pid,NULL,0);
    waitpid(grep_pid,NULL,0);
    return 0; 
}
