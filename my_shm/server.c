#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include"commom.h"


int main()
{
    key_t k=ftok(PATHNAME,PROJ_ID);
    printf("key:%p\n",k);
    int shmid=shmget(k,SIZE,IPC_CREAT|IPC_EXCL|0666);
    if(shmid<0){
        perror("shmget error\n");
        return 1;
    }
    printf("shmid:%d\n",shmid);
    char* str=(char*)shmat(shmid,NULL,0);
    while(1){
        sleep(1);
        printf("str:%s\n",str);
    }
    shmctl(shmid,IPC_RMID,NULL);
    return 0;
}
