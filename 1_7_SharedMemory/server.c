#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include"comm.h"

int main()
{
    umask(0);
    key_t key=ftok(PATHNAME,PROJ_ID);
    printf("key:%d\n",key);
    int shmid=shmget(key,SIZE,IPC_CREAT|IPC_EXCL|0666);
    if(shmid<0){
        perror("shmget fail!\n");
        exit(-1);
    }    
    char* str=(char*)shmat(shmid,NULL,0);
    printf("client:");
    while(1){
        printf("%s\n",str);   
        sleep(3);
    }  
    shmdt(str);
    shmctl(shmid,IPC_RMID,NULL);  
    return 0;
}
