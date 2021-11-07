#pragma once
#include<iostream>
#include<unistd.h>
#include<queue>
#include<math.h>

#define NUM 5


class Task
{
public:
    Task(){}
    Task(int _b):base(_b){}
    ~Task(){}
    void Run()
    {
        std::cout<<"thread id is["<<pthread_self()<<"] #task run ... done:base# "<<base<<" pow is# "<<pow(base,2)<<std::endl;
    }
private:
    int base;
};

class ThreadPool
{
private:
    std::queue<Task*> q;
    int max_num;
    pthread_mutex_t lock;
    pthread_cond_t cond;   // only for consumer--ThreadPool thread
public:
    void LockQueue()
    {
        pthread_mutex_lock(&lock); 
    }
    void UnlockQueue()
    {
        pthread_mutex_unlock(&lock);
    }
    bool IsEmpty()
    {
        return q.size()==0;
    }
    void ThreadWait()
    {
        pthread_cond_wait(&cond,&lock);
    }
    void ThreadWakeUp()
    {
        //pthread_cond_signal(&cond);
        pthread_cond_broadcast(&cond);
    }
public:
    ThreadPool(int _max=NUM):max_num(_max){}
    static void* Routine(void* arg)
    {
        ThreadPool* tp=(ThreadPool*)arg;
        while(true){
           tp->LockQueue();
            while(tp->IsEmpty()){
               tp->ThreadWait();
            }
            Task t;
            tp->Get(t);
            
            tp->UnlockQueue();
            t.Run();
        }
    }
    void Put(Task& in)  //server
    {
        LockQueue();
        q.push(&in); 
        UnlockQueue();
        ThreadWakeUp();
    }
    void Get(Task& out)  // consumer
    {
        //不需要加锁，因为Get函数在被调用的地方是临界区，已经被被加锁保护了(line 63)
        Task* t=q.front();
        q.pop();
        out=*t;
    }
    void ThreadPoolInit()
    {
        pthread_mutex_init(&lock,nullptr);
        pthread_cond_init(&cond,nullptr);
        pthread_t t;
        for(int i=0;i<max_num;i++){
            pthread_create(&t,nullptr,Routine,this);
        }
    }
    ~ThreadPool()
    {
        pthread_mutex_destroy(&lock);
        pthread_cond_destroy(&cond);
    }
};
