#include"common.h"


int main()
{
  key_t key=ftok(PATH_NAME,PROJ_ID);
  int shmid =shmget(key,PAGE_SIZE,IPC_CREAT|0666);
  char* msg=(char*)shmat(shmid,NULL,0);
  if(msg==(char*)-1){
    perror("client shmat fail!\n");
    exit(1);
  }else{
    printf("client attach success!\n");
  }

  while(1){
    printf("[Enter Massage]# ");
    fflush(stdout);
    fgets(msg,1024,stdin);
  }
  if(shmdt(msg)<0){
    perror("client shmdt fail!\n");
  }
  return 0;
}
