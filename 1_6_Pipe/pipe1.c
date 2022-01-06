/*************************************************************************
	> File Name: pipe1.c
	> Author: 
	> Mail: 
	> Created Time: Thu 06 Jan 2022 08:46:22 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>

int main()
{
    int pipefd[2]={0};
    pipe(pipefd);
    pid_t pid=fork();
    if(pid<0){
        perror("fork fail!\n");
        exit(-1);
    }
    if(pid==0){
        //child
        close(pipefd[0]);
        char tmp[1024]={0};
        fgets(tmp,1023,stdin);
        write(pipefd[1],tmp,1023);
        exit(0);
    }
    if(pid>0){
        char buff[1024]={0};
        close(pipefd[1]);
        size_t num=read(pipefd[0],buff,1023);
        if(num<0){
            perror("read fail!\n");
            exit(-1);
        }
        printf("father read from pipe:%s",buff);
        int status=0;
        int ret= waitpid(pid,&status,0);
        
    }    

    return 0;
}
