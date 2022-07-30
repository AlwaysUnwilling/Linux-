#include<iostream>
#include<pthread.h>

pthread_mutex_t lock;
pthread_cond_t cond;
void* routine(void* arg)
{
    char* threadId=(char*) arg;
    while(true){
        pthread_cond_wait(&cond,&lock);
        std::cout<<threadId<<" is Running..."<<std::endl;
    }
    return nullptr;
}
int main()
{
    pthread_mutex_init(&lock,nullptr);
    pthread_cond_init(&cond,nullptr);
    pthread_t t1,t2,t3;
    pthread_create(&t1,nullptr,routine,(void*)"Thread 1");
    pthread_create(&t1,nullptr,routine,(void*)"Thread 2");
    pthread_create(&t1,nullptr,routine,(void*)"Thread 3");
    
    while(true){
        getchar();
        pthread_cond_signal(&cond);
    }

    pthread_join(t1,nullptr);
    pthread_join(t2,nullptr);
    pthread_join(t3,nullptr);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}