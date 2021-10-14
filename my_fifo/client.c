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
    int fd=open("./fifo",O_WRONLY,0666);
    if(fd<0){
        perror("open error\n");
        return 1;
    }
    char buf[64];
    while(1){
        printf("Please Enter Message:");
        fflush(stdout);
        ssize_t num_r =read(0,buf,sizeof(buf)-1);
        buf[num_r]=0;
        if(num_r>0){
            ssize_t num_w=write(fd,buf,num_r); 
        }
    }
    return 0;
}
