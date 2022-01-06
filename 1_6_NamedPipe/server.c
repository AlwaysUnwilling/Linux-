#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#define FIFO_FILE "./fifo"

int main()
{
    umask(0);
    if(-1==mkfifo(FIFO_FILE,0666)){
        perror("mkfifo fail!\n");
        exit(-1);
    }
    int fd=open(FIFO_FILE,O_RDONLY);
    if(fd>=0){
        char buf[64];
        while(1){
            ssize_t s=read(fd,buf,sizeof(buf)-1);
            if(s>0){
                buf[s]=0;
                printf("client: %s",buf);
            }else if(s==0){
                printf("client quick,me too!\n");
                exit(0);
            }else{
                perror("read fail!\n");
                exit(1);
            }
        }
    }
    return 0;
}
