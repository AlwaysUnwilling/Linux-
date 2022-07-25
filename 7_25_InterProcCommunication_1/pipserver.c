#include"common.h"


int main()
{
  if(mkfifo(FILE_NAME,0666)==0){
    printf("fifo success!\n");
  }else{
    perror("mkfifo error!\n");
    return 1;
  }
  int fd=open(FILE_NAME,O_RDONLY);
  if(fd<0){
    perror("open error!\n");
    return 2;
  }
  char* buff[1024]={0};
  while(1){
    buff[0]=0;
    ssize_t s=read(fd,buff,sizeof(buff)-1);
    if(s<0){
      perror("read error\n");
      return 3;
    }else if(s==0){
      printf("client quit!\n");
      break;
    }else{
      buff[s-1]=0;
      printf("[client say]# %s\n",buff);
    }
  }
  return 0;
}
