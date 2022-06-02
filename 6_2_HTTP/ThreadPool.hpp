#pragma once 

#include<iostream>
#include<queue>
#include<sys/types.h>
#include<pthread.h>
#include"Task.hpp"
#include"Log.hpp"

#define CAPACITY 5

class ThreadPool
{
  private:
    int num;                      //线程池容量
    bool stop;                    //线程池的运行状态
    std::queue<Task> task_queue;   //任务队列
    pthread_mutex_t lock;
    pthread_cond_t cond;
    static ThreadPool* inst;
  private:
    void LockQueue()
    {
       pthread_mutex_lock(&lock);         
    }
    void UnlockQueue()
    {
      pthread_mutex_unlock(&lock);
    }
    void ThreadWait()
    {
      pthread_cond_wait(&cond,&lock);
    }
    void ThreadWakeUp()
    {
      pthread_cond_signal(&cond);
    }
    bool IsStop()
    {
      return stop;
    }
    bool IsQueueEmpty()
    {
      return task_queue.empty();
    }
    static void* ThreadRoutine(void* arg)
    {
      ThreadPool* tpThis=(ThreadPool*)arg; 
      while(true){
        Task t;
        tpThis->LockQueue();
        while(tpThis->IsQueueEmpty()){  //防止假唤醒
          tpThis->ThreadWait();
        }
        tpThis->PopTask(t);
        tpThis->UnlockQueue();
        t.ProcessOn();
      }
      return nullptr;
    }
  private:
    ThreadPool(int _num=CAPACITY)
      :num(_num),stop(false)
    {}
  public: 
    ThreadPool(const ThreadPool&)=delete;
    static ThreadPool* GetInstance()
    {
      static pthread_mutex_t _mutex=PTHREAD_MUTEX_INITIALIZER;
      if(inst==nullptr){
        pthread_mutex_lock(&_mutex);
        if(inst==nullptr){
          inst=new ThreadPool();
          inst->ThreadPoolInit();
        }
        pthread_mutex_unlock(&_mutex);
      }
      return inst;
    }
    bool ThreadPoolInit()
    {
      pthread_mutex_init(&lock,nullptr);
      pthread_cond_init(&cond,nullptr);
      for(int i=0;i<num;++i){
        pthread_t tid;
        if(pthread_create(&tid,nullptr,ThreadRoutine,this)!=0){
          LOG(FATAL,"pthread pool create error!");
          return false;
        }
      }
      LOG(INFO,"pthreadpool create success ");
      return true;
    }
    void PushTask(const Task& task)  //添加任务
    {
      LockQueue();
      task_queue.push(task);
      UnlockQueue();
      ThreadWakeUp();
    }
    void PopTask(Task& task)         //取出任务
    {
      task=task_queue.front();
      task_queue.pop();
    }
    ~ThreadPool()
    {
      pthread_mutex_destroy(&lock);
      pthread_cond_destroy(&cond);
    }
};

ThreadPool* ThreadPool::inst=nullptr;
