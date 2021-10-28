#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>


int bowl=0;//默认0表示碗中没有饭
pthread_cond_t cond;//实现线程间对bowl变量访问的同步操作
pthread_mutex_t mutex;//保护bowl变量的访问操作


void* thr_cook(void* arg)
{
    while(1){
        //加锁
        pthread_mutex_lock(&mutex);
        if(bowl!=0){//表示有饭，不满足做饭的条件
                    //让厨师线程等待，等待之前先解锁，被唤醒之后再加锁
            pthread_cond_wait(&cond,&mutex);//该接口中完成了解锁、休眠、被唤醒后加锁三步操作；并且解锁和休眠操作是一步完成的，保证了原子操作
        }
        bowl=1;//能运行到这步，表示没饭，bowl=0；则做一碗饭，将bowl置为1；
        printf("I made a bowl of rice\n");
        //唤醒顾客吃饭
        pthread_cond_signal(&cond);
        //解锁
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
void* thr_customer(void* arg)
{
    while(1){
        //加锁
        pthread_mutex_lock(&mutex);
        if(bowl!=1){//没有饭，不满足吃饭条件，则等待
                    //没有饭则等待，等待之前先解锁，被唤醒后加锁
            pthread_cond_wait(&cond,&mutex);
        }
        bowl=0;//能运行到这步，表示有饭，bowl=1；吃完饭，将bowl置为0；
        printf("I had a bowl of rice.It was delicious\n");
        //唤醒厨师做饭
        pthread_cond_signal(&cond);
        //解锁
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
int main()
{
    pthread_t cook_tid,customer_tid;
    int ret;
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond,NULL);
    ret=pthread_create(&cook_tid,NULL,thr_cook,NULL);
    if(ret!=0){
        perror("pthread_create error\n");
        return -1;
    }
    ret=pthread_create(&customer_tid,NULL,thr_customer,NULL);
    if(ret!=0){
        perror("pthread_create error\n");
        return -1;
    }

    pthread_join(cook_tid,NULL);
    pthread_join(customer_tid,NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond); 
    return 0;
}
