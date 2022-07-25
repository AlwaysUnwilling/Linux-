#include"common.h"


int main()
{
  int fd=open(FILE_NAME,O_WRONLY);
  if(fd<0){
    perror("client open error!\n");
    return 1;
  }
  char msg[1024]={0};
  while(1){
    printf("please Enter Msg: ");
    fflush(stdout);
    char* ret=fgets(msg,1023,stdin);
    msg[strlen(msg)-1]=0;
    if(ret==NULL){
      perror("fgets error!\n");
      continue;
    }
    write(fd,msg,1023);
  }
  return 0;
}
