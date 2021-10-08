#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
int main()
{
    //close(1);
    int fd=open("log.txt",O_CREAT|O_WRONLY,0644);
    if(fd<0){
        perror("open error\n");
        return 1;
    }
    dup2(fd,1);
    close(fd);
    const char* str="hello world:write\n";
    const char* str1="hello world:printf\n";
    const char* str2="hello world:fprintf\n";
    write(fd,str,strlen(str));
    printf("%s",str1);
    fprintf(stdout,"%s",str2);

    fork();

    fflush(stdout);
    close(fd);
    return 0;
}
