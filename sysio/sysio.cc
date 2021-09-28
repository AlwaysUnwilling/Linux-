#include<iostream>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

using namespace std;

int main()
{
    int fd=-1;
    umask(0);//将当前进程的文件创建权限掩码设置为0--仅当前进程有效
    fd=open("./test.txt",O_RDWR|O_CREAT|O_EXCL,0777);
    if(fd<0){
        perror("open error\n");
        return -1;
    }
    char* ptr="It is a fine day today.\n";
    int ret= write(fd,ptr,strlen(ptr));
    if(ret<0){
        perror("write error\n");
        return -1;
    }
    printf("ret:%d\n",ret);
    close(fd);
    return 0;
}
