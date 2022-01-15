/*************************************************************************
	> File Name: pthreadctr.c
	> Author: 
	> Mail: 
	> Created Time: Sat 15 Jan 2022 06:06:44 PM CST
    > About:Thread synchronization
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

pthread_mutex_t lock;
pthread_cond_t cond;


void* route_pthread2(void* arg)
{
    const char* movement=(char*)arg;
    while(1){
        pthread_cond_wait(&cond,&lock);
        printf("%s\n",movement);
    }

}
void* route_pthread1(void* arg)
{
   const char* cmd=(char*)arg;
    while(1){
        sleep(rand()%3+1);
        printf("%s\n",cmd);
        pthread_cond_signal(&cond);
    }
}
int main()
{
    pthread_t tid1,tid2;
    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&cond,NULL);
    pthread_create(&tid1,NULL,route_pthread1,(void*)"this is cmd");
    pthread_create(&tid2,NULL,route_pthread2,(void*)"Executing command");

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}

