#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>


int ticket=100;
pthread_mutex_t mutex;

void* thr_scalpers(void* arg)
{
    while(1){
        //加锁一定是只保护临界资源的访问
        pthread_mutex_lock(&mutex);
        if(ticket>0){
            //有票就一直抢
            usleep(1000);
            printf("I got a ticket:%d\n",ticket);
            --ticket;
            pthread_mutex_unlock(&mutex);
        }else{
            //加锁后在任意有可能退出线程的地方都要解锁
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
    }
    return NULL;
}
int main()
{
    //互斥所的初始化要在线程创建之前
    pthread_mutex_init(&mutex,NULL);
    pthread_t tid[4];
    for(int i=0;i<4;i++){
        int ret=pthread_create(&tid[i],NULL,thr_scalpers,NULL);
        if(ret!=0){
            perror("thread create error!\n");
            return -1;
        }
    }
    for(int i=0;i<4;i++){
        pthread_join(tid[i],NULL);
    }
    pthread_mutex_destroy(&mutex);
    return 0; 
}
