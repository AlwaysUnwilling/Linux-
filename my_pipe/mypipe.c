#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main()
{
    int pipefd[2]={0};
    int pip=pipe(pipefd);
    if(pip<0){
        perror("pipe error\n");
        return -1;
    }
    pid_t id=fork();
    if(id==0){
       //child
        close(pipefd[0]);
        const char* msg="I am a child.,.!\n";
        while(1){
            write(pipefd[1],msg,strlen(msg));
            sleep(1);
        }
    }else if(id>0){
        //father
        close(pipefd[1]);
        char buf[64]={0};
        while(1){
           ssize_t num= read(pipefd[0],buf,sizeof(buf)-1);
            if(num>0){
                buf[num]==0;//文件读取出来的字符串没有'\0',这里添加0作为字符串的结束标志。buf[num]是实际读取到的字符串的下一个字符
                printf("father get message:%s\n",buf);
            }
        }
    }else{
        perror("fork error\n");
        return -1;
    }

    return 0;
}
