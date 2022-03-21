#ifndef __RINGQUEUE_HPP__
#define __RINGQUEUE_HPP__ 

#include<iostream>
#include<vector>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

template<class T>
class RingQueue 
{
  private:
    std::vector<T> v;
    sem_t sem_blank;  //productor
    sem_t sem_data;      //comsumer
    int pro_step;
    int com_step;    
    size_t max_cap;
  private:
    void P(sem_t& sem_arg)
    {
      sem_wait(&sem_arg);
    }
    void V(sem_t& sem_arg)
    {
      sem_post(&sem_arg);
    }
  public:
    RingQueue(size_t cap)
      :pro_step(0),com_step(0),max_cap(cap)
    {
      v.reserve(max_cap);
      sem_init(&sem_blank,0,max_cap);
      sem_init(&sem_data,0,0);
    }
    void Get(T& out)
    {
      P(sem_data);
      //消费
      out=v[com_step++];
      com_step%=max_cap;
      V(sem_blank);
    }
    void Put(const T& in)
    {
      P(sem_blank);
      //生产
      v[pro_step++]=in;
      pro_step%=max_cap;
      V(sem_data);
    }
    ~RingQueue()
    {
      sem_destroy(&sem_blank);
      sem_destroy(&sem_data);
      pro_step=com_step=0;
    }
};


#endif
