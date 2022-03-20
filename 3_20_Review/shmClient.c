#include"shmCommon.h"


int main()
{
  key_t key=KEY;
  int fd=shmget(key,SIZE,0);
  char* memery=(char*)shmat(fd,NULL,0);

  while(1)
  {
    printf("Enter Massage: ");
    memery=fgets(memery,SIZE,stdin);
  }
  shmdt(memery);
  return 0;
}
