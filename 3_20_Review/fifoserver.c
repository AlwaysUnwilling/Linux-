#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>

#define FIFO_FILE "./fifo"


int main()
{
  umask(0);
  if(mkfifo(FIFO_FILE,0664)<0)
  {
    perror("mkfifo error!");
    exit(1);
  }
  int fd=open(FIFO_FILE,O_RDONLY);
  if(fd>=0)
  {
    char buf[64]={0};
    while(1)
    {
      ssize_t s=read(fd,buf,63);
      if(s>0)
      {
        buf[s]=0;
        printf("GetMsg: %s\n",buf);
      }
      else if(s==0){
        printf("client quit!\n");
        break;
      }
      else{
        perror("read error!\n");
        break;
      }
    }
  }
  else{
    perror("open fail!\n");
    exit(2);
  }
  return 0;
}
