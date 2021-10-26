#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

int a=100;
void* thr_start(void* arg)
{
    strcpy(arg,"i modify your message!");
    while(1){
        a=200;
        printf("i am thread: %s---%d\n",(char*)arg,a);
        sleep(1);
    }
    return NULL;
}
int main()
{
    pthread_t tid;
    char ptr[]="hello world!";
    //pthread_create(获取线程ID，线程属性（NULL），线程入口函数，参数)
    int ret=pthread_create(&tid,NULL,thr_start,(void*)ptr);
    if(ret!=0){
        perror("create thread error\n");
        return -1;
    }
    while(1){
        printf("i am main: %s---%d\n",ptr,a);
        sleep(1);
    }
    return 0;
}
