#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define NUM 128


int main()
{
    int pipefd[2]={0};
    char buff[NUM];
    int len;

    if(pipe(pipefd)==-1){
        perror("pipe fail!\n");
        exit(-1);
    }

    //read from stdin
    while(fgets(buff,NUM,stdin)){
        len=strlen(buff);
        //write int pipe
        if(write(pipefd[1],buff,len)!=len){
            perror("write to pipe!\n");
            break;
        }
        memset(buff,0,sizeof(buff));

        //read from pipe
        if(len=read(pipefd[0],buff,NUM)==-1){
            perror("read pipe fail!\n");
            break;
        }
        
        printf("buff:%s",buff);

        //wirte to stdout
        if(write(1,buff,len)!=len){
            perror("write to stdout !\n");
            break;
        }
        
    }
    return 0;
}
