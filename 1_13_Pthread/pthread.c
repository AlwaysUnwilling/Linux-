#include<sys/stat.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<pthread.h>



void* thread_run(void* arg)
{
    while(1){
        printf("%s,%lu,pid:%d\n",(char*)arg,pthread_self(),getpid());
        sleep(1);
    }
    //pthread_exit((void*)10);
    //return (void*)10;
}
int main()
{
    pthread_t tid;
    pthread_create(&tid,NULL,thread_run,"thread 1");
    printf("main :%lu,pid:%d\n",pthread_self(),getpid());
    sleep(10);
    pthread_cancel(tid);
    printf("new thread %lu be canceled!\n",tid);

    void* ret=NULL;
    pthread_join(tid,&ret);
    printf("thread quit code:%d\n",(long long)ret);
    return 0;
}
