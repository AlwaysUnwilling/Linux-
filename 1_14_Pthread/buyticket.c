/*************************************************************************
	> File Name: buyticket.c
	> Author: 
	> Mail: 
	> Created Time: Fri 14 Jan 2022 06:46:58 PM CST
    > About:Use multi-thread simulation to purchase tickets.
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

int ticket=100;
pthread_mutex_t lock;


void* buy_ticket(void* arg)
{
    int num=(int)arg;
    while(1){
        usleep(1000);
        pthread_mutex_lock(&lock);
        if(ticket>0){
            printf("tid[%d]get a ticket! ticket left:%d! pthread_self():%lu\n",num,ticket,pthread_self());
            ticket--;
            pthread_mutex_unlock(&lock);
        }else{
            pthread_mutex_unlock(&lock);
            printf("none ticket!\n");
            break;
        }
    }
}
int main()
{
    pthread_t tid[4];
    pthread_mutex_init(&lock,NULL);
    for(int i=0;i<4;++i){
        pthread_create(tid+i,NULL,buy_ticket,(void*)i);
    }

    for(int i=0;i<4;++i){
        pthread_join(tid[i],NULL);
    }
    pthread_mutex_destroy(&lock);
    return 0;
}


