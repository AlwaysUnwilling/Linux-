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
    int shmid=shmget(k,SIZE,0);
    if(shmid<0){
        perror("shmget error\n");
        return 1;
    }
    printf("shmid:%d\n",shmid);
    char* str=(char*)shmat(shmid,NULL,0);
    char c='a';
    for(;c<='z';c++){
        str[c-'a']=c;
        sleep(5);
    }

    return 0;
}
