#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>

#define FIFO_FILE "./fifo"

int main()
{
  int fd=open(FIFO_FILE,O_WRONLY);
  if(fd>=0)
  {
    char buf[64]={0};
    while(1)
    {
      printf("Please Enter massage: ");
      fgets(buf,sizeof(buf)-1,stdin);
      buf[strlen(buf)-1]=0;
      ssize_t s=write(fd,buf,sizeof(buf)-1);
      if(s<0)
      {
        perror("write error!\n");
        exit(3);
      }
    }
  }
  return 0;
}
