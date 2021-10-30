#include"pthreadpool.hpp"
#include<unistd.h>


void test_func(int data)
{
    int sec=data%3+1;
    printf("tid:%p -- get data:%d,sleep:%d\n",pthread_self(),data,sec);
    sleep(sec);
}
void tmp_func(int data)
{
    printf("tid:%p -- tmp_func\n",pthread_self());
    sleep(1);
}
int main()
{
    ThreadPool pool;
    for(int i=0;i<5;i++){
        ThreadTask task;
        if(i%2==0){
            task.SetTask(i,test_func); 
        }else{
            task.SetTask(i,tmp_func);
        }
        pool.TaskPush(task);
    }
    sleep(1);
    return 0;
}
