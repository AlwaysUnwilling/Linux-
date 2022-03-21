#ifndef __BLOCKQUEUE_HPP__
#define __BLOCKQUEUE_HPP__  

#include<iostream>
#include<queue>
#include<pthread.h>
#include<unistd.h>


class Task
{
  private:
    int x;
    int y;
  public: 
    Task(int _x,int _y)
      :x(_x),y(_y)
    {} 
    int First()
    {
      return x;
    }
    int Second()
    {
      return y;
    }
    int Sum()
    {
      return x+y;
    }
};
template<class T>
class BlockQueue 
{
  private:
    std::queue<T> q;
    size_t cap;
    pthread_mutex_t lock;
    pthread_cond_t full;
    pthread_cond_t empty;
  private:
    void LockQueue()
    {
      pthread_mutex_lock(&lock);
    }
    void UnlockQueue()
    {
      pthread_mutex_unlock(&lock);
    }
    void WakeUpComsumer()
    {
      pthread_cond_signal(&full);
    }
    void WakeUpProductor()
    {
      pthread_cond_signal(&empty);
    }
    void ComsumerWait()
    {
      pthread_cond_wait(&full,&lock);
    }
    void ProductorWait()
    {
      pthread_cond_wait(&empty,&lock);
    }
    bool IsFull()
    {
      return q.size()>=cap;
    }
    bool IsEmpty()
    {
      return q.empty();
    }
  public:
    BlockQueue(int _cap)
      :cap(_cap)
    {
      pthread_mutex_init(&lock,nullptr);
      pthread_cond_init(&full,nullptr);
      pthread_cond_init(&empty,nullptr);
    }

    void Put(const T& in)
    {
      LockQueue();
      while(IsFull()){
       WakeUpComsumer();
       ProductorWait();
      }
      q.push(in);
      UnlockQueue();
    } 
    void Get(T& out)
    {
      LockQueue();
      while(IsEmpty()){
        WakeUpProductor();
        ComsumerWait();
      }
      out=q.front();
      q.pop();
      UnlockQueue();
    }
    ~BlockQueue()
    {
      pthread_mutex_destroy(&lock);
      pthread_cond_destroy(&full);
      pthread_cond_destroy(&empty);
    }
};


#endif 
