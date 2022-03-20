#include"shmCommon.h"



int main()
{
  key_t key=KEY;
  int fd=shmget(key,SIZE,IPC_CREAT | IPC_EXCL |0664);
  if(fd<0)
  {
    perror("shmget error!\n");
    exit(1);
  }
  char* memery=(char*)shmat(fd,NULL,0);
  while(1)
  {
    printf("%s\n",memery);
    sleep(1);
  }

  shmdt(memery);
  shmctl(fd,IPC_RMID,NULL);
  return 0;
}
