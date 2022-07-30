#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#define NUM 100000
const int tidNum=5;
int tickets=NUM;
pthread_mutex_t lock;

void* GrabingTickets(void* arg)
{
    int id=(int)arg;
    while(1){
        pthread_mutex_lock(&lock);
        if(tickets>0){
            usleep(1000);
            // std::cout<<"Thread "<<id<<" Grabing..."<<" Thread_ID: "<<pthread_self()<<std::endl;
            // tickets--;
            // std::cout<<"tickets left: "<<tickets<<std::endl;
            printf("Thread [%d] Thread_ID: %lu Grabing...tickets left[%d]\n",id,pthread_self(),tickets--);
            pthread_mutex_unlock(&lock);
            sleep(1);
        }else{
            pthread_mutex_unlock(&lock);
            break;
        }
    }
}
int main()
{
    pthread_mutex_init(&lock,NULL);
    pthread_t tid[tidNum];
    for(int i=0;i < tidNum;++i){
        pthread_create(&tid[i],NULL,GrabingTickets,(void*)i);
        // std::cout<<"success!"<<std::endl;
    }

    for(int i=0;i < tidNum;++i){
        pthread_join(tid[i],NULL);
    }
    pthread_mutex_destroy(&lock);
    return 0;
}
