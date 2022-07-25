#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>

void handler(int signo)
{
  int status=0;
  pid_t ret=waitpid(-1,&status,0);
  if(ret<0){
    perror("waitpid error!\n");
    exit(4);
  }
  if(!WIFEXITED(status)){
    printf("child proc exit code:%d\n",WEXITSTATUS(status));
  }else{
    printf("child proc get a sig:%d\n",WIFEXITED(status));
  }
}
int main()
{
  int pipfd[2]={0};
  if(pipe(pipfd)<0){
    perror("pipe error!\n");
    return 1;
  }
  pid_t pid=fork();
  if(pid<0){
    perror("fork error!\n");
    return 2;
  }else if(pid==0){
    //child write
    close(pipfd[0]);
    const char* msg="Hello!I am childproc!";
    ssize_t num=write(pipfd[1],msg,strlen(msg));
    if(num<0){
      perror("child write error!\n");
      exit(3);
    }
    sleep(10);
    exit(0);
  }else{
    //farther read;
    close(pipfd[1]);
    signal(SIGCHLD,handler);
    char* buff[1024]={0};
    while(1){
      buff[0]=0;
      ssize_t s=read(pipfd[0],buff,1023);
      if(s<0){
        perror("read error!\n");
        return 5;
      }else if(s==0){
        perror("child exit!\n");
        wait(NULL);
        break;
      }else{
        buff[s-1]=0;
        printf("[child say]# %s\n",buff);
      }
    }
  }

  return 0;
}
