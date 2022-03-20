#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>


int main()
{
  int pipefd[2]={-1,-1};
  if(pipe(pipefd)<0)
  {
    perror("pipe error!\n");
    exit(1);
  }
  pid_t pid=fork();
  if(pid==0)
  {
    close(pipefd[0]);
    const char* msg="chat with me!\n";
    int count=10;
    while(count--)
    {
      write(pipefd[1],msg,strlen(msg));
      sleep(1);
    }
    exit(0);
  }
  char buff[64]={0};
  while(1)
  {
    close(pipefd[1]);
    size_t s=read(pipefd[0],buff,sizeof(buff)-1);
    if(s>0)
    {
      printf("GetMsg:%s\n",buff);
      sleep(1);
    }
    if(s<0)
    {
      perror("read error!\n");
      break;
    }
    if(s==0)
    {
      printf("writer quit!\n");
      break;
    }
  }
  wait(NULL);
  return 0;
}
