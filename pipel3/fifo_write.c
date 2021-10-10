#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
    umask(0);
    int ret=mkfifo("./test.fifo",0664);
    if(ret<0 && errno!=EEXIST){
        perror("mkfifo error\n");
        return -1;
    }
    int fd=open("./test.fifo",O_WRONLY);
    if(fd<0){
        perror("open error\n");
        return 1;
    }
    printf("open fifo success\n");
    int i=0;
    while(1){
        char buf[1024]={0};
        sprintf(buf,"今天好冷啊...+%d",i++);//将buf中的数据打印到标准输出
        write(fd,buf,strlen(buf));
        sleep(1);
    }
    close(fd);
    return 0;
}
