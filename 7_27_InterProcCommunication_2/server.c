#include"common.h"



int main()
{
  //获取唯一key值以便创建新的唯一共享内存
  key_t key=ftok(PATH_NAME,PROJ_ID);
  if(key<0){
    perror("ftok error!\n");
    exit(1);
  }
  //IPC_CREAT|IPC_EXCL 该俩个宏一起使用可以创建出一个全新的唯一的共享内存，否则直接报错
  //如果只使用IPC_CREATE则该函数调用一定成功：如果不存在该共享内存则新创建；如果存在
  //则返回存在的共享内存的id
  int shmid=shmget(key,PAGE_SIZE,IPC_CREAT|IPC_EXCL|0666);
  if(shmid<0){
    perror("shmget error!\n");
    exit(2);
  }

  //挂接
  char* addr=(char*)shmat(shmid,NULL,0);
  if(addr==(char*)-1){
    perror("server attach fail!\n");
    exit(4);
  }else{
    printf("server attach success!\n");
  }

  int count=10;
  while(count--){
    printf("[client say]# %s\n",addr);
    sleep(1);
  }

  //取消关联
  if(shmdt(addr)<0){
    perror("server shmdt fail!\n");
  }
  if(shmctl(shmid,IPC_RMID,NULL)<0){
    perror("shmctl error!\n");
    exit(3);
  }
  return 0;
}
