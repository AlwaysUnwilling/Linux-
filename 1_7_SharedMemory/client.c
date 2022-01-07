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
    key_t key=ftok(PATHNAME,PROJ_ID);
    printf("key:%d\n",key);
    int shmid=shmget(key,SIZE,0);
    if(shmid<0){
        perror("shmget fail!\n");
        exit(-1);
    }    
    char* str=(char*)shmat(shmid,NULL,0);
    char ch='A';
    while(ch<='Z'){
        str[ch-'A']=ch;  
        ch++;
        sleep(3);
    }  
    shmdt(str);  
    return 0;
}
