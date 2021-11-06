#pragma once

#include<iostream>
#include<semaphore.h>
#include<vector>

#define NUM 10

class RingQueue
{
private:
    std::vector<int> v;
    int max_cap;
    int c_index;
    int p_index;
    sem_t sem_blank;//生产者
    sem_t sem_data;//消费者
private:
    void P(sem_t &s)
    {
        sem_wait(&s);
    }
    void V(sem_t &s)
    {
        sem_post(&s);
    }
public:
    RingQueue(int _cap=NUM):max_cap(_cap),v(_cap)
    {
        sem_init(&sem_data,0,0); 
        sem_init(&sem_blank,0,max_cap);
        c_index=p_index=0;
    }
    void Get(int& out)
    {
        P(sem_data);
        //消费
        out=v[c_index];
        c_index++;
        c_index%=max_cap;
        V(sem_blank);
    }
    void Put(const int in)
    {
        P(sem_blank);
        //生产
        v[p_index]=in;
        p_index++;
        p_index%=max_cap;
        V(sem_data);
    }
    ~RingQueue()
    {
        sem_destroy(&sem_blank);
        sem_destroy(&sem_data);
    }
};
