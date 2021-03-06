#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#define FIFO_FILE "./fifo"

int main()
{
    umask(0);
    if(-1==mkfifo(FIFO_FILE,0666)){
        perror("mkfifo error\n");
        return 1;
    }
    int fd=open(FIFO_FILE,O_RDONLY);
    if(fd>=0){
        char buf[64];
        while(1){
            ssize_t s=read(fd,buf,sizeof(buf)-1);
            if(s>0){
                buf[s]=0;
                printf("client# %s",buf);
            }
            else if(s==0){
                //
                printf("Client quit! Me too.\n");
                break;
            }
            else{
                perror("read error\n");
                break;
            }
        }
    }
    close(fd);
    return 0;
}
