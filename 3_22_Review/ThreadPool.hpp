#ifndef __THREADPOOL_HPP__
#define __THREADPOOL_HPP__ 

#include<iostream>
#include<queue>
#include<pthread.h>
#include<unistd.h>

class Task
{
  public:
    Task()
    {}
    void Run()
    {
      std::cout<<"Thread ID: "<<pthread_self()<<" task running..."<<std::endl;
    }
};


class ThreadPool 
{
  private:
    std::queue<Task*> q;
    size_t max_th;
    pthread_mutex_t lock;
    pthread_cond_t cond;  //只能让消费者等
  private:
    void LockQueue()
    {
      pthread_mutex_lock(&lock);
    }
    void UnlockQueue()
    {
      pthread_mutex_unlock(&lock);
    } 
    void WakeUpProductor()
    {
      pthread_cond_signal(&cond);
    }
    void ThreadWait()
    {
      pthread_cond_wait(&cond,&lock);
    }
    void WakeUpThread()
    {
      pthread_cond_signal(&cond);
    }
    bool IsEmpty()
    {
      return q.empty();
    }
    static void* Routine(void* arg)
    {
      ThreadPool* pthis=(ThreadPool*)arg;
      while(true)
      {
        pthis->LockQueue();
        while(pthis->IsEmpty())   //防止异常唤醒
        {
          pthis->WakeUpProductor();
          pthis->ThreadWait();
        }
        Task t;
        pthis->Get(&t);
        pthis->UnlockQueue();
        t.Run();
      }
    }
  public:
    ThreadPool(int max)
      :max_th(max)
    {}
    void ThreadPoolInit()
    {
      pthread_mutex_init(&lock,nullptr);
      pthread_cond_init(&cond,nullptr);
      for(size_t i=0;i<max_th;++i)
      {
        pthread_t t;
        pthread_create(&t,nullptr,Routine,(void*)this);
      }
    }
    void Put(Task* t)
    {
      LockQueue();
      q.push(t);
      UnlockQueue();
      WakeUpThread();
    }
    void Get(Task* t)
    {
      t=q.front();
      q.pop();
    }
    ~ThreadPool()
    {
      pthread_mutex_destroy(&lock);
      pthread_cond_destroy(&cond);
    }
};



#endif 
