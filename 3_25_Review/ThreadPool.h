#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__ 

#include<iostream>
#include<queue>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include"protocol.hpp"

#define NUM 5

class Task
{
  private:
    int sock;
  public:
    Task(int _sock=-1)
      :sock(_sock) 
    {}
    void Run();
    ~Task()
    {
      if(sock>=0){
        close(sock);
      }
    }
};

class ThreadPool 
{
  private:
    std::queue<Task*> q;
    pthread_mutex_t lock;
    pthread_cond_t cond;
    size_t max_cap;
  private:
    ThreadPool()
      :max_cap(NUM)
    {}
    static ThreadPool obj;
    static void* Routine(void* arg);
    void LockQueue();
    void UnlockQueue();
    bool IsFull();
    bool IsEmpty();
    void WakeUpThread();
    void ThreadWait();
  public:
    static ThreadPool* GetThreadObj()
    {
      return &obj;
    }
    ThreadPool(const ThreadPool&)=delete;
    void ThreadPoolInit();
    void Put(Task* t);
    void Get(Task*& t);
    ~ThreadPool()
    {
      max_cap=0;
      pthread_mutex_destroy(&lock);
      pthread_cond_destroy(&cond);
    }
};

#endif 
