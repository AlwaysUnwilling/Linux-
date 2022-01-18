#ifndef __RINGQUEUE_H__
#define __RINGQUEUE_H__

#include<iostream>
#include<pthread.h>
#include<stdlib.h>
#include <semaphore.h>
#include<vector>
#include<unistd.h>

#define NUM 5
namespace my_RingQueue
{
    template<class T>
    class RingQueue
    {
    private:
        void P(sem_t& s)
        {
            sem_wait(&s); 
        }
        void V(sem_t& s)
        {
            sem_post(&s); 
        }
    public:
        RingQueue(size_t cap=NUM)
        :_cap(cap)
        ,p_index(0)
        ,c_index(0)
        ,_v(_cap)
        {
            RingQueueInit(); 
        }
        void RingQueueInit()
        {
            sem_init(&sem_blank,0,_cap);
            sem_init(&sem_data,0,0);
            //pthread_mutex_init(&lock,nullptr);
        }
        void Push(const T& data)
        {
            P(sem_blank);
            //生产
            _v[p_index]=data;
            p_index++;
            p_index%=_cap;
            V(sem_data);
        }
        void Get(T& data)
        {
            P(sem_data);
            //消费
            data=_v[c_index];
            c_index++;
            c_index%=_cap;
            V(sem_blank);
        }
        ~RingQueue()
        {
            sem_destroy(&sem_blank);
            sem_destroy(&sem_data);
            //pthread_mutex_destroy(&lock);
            p_index=c_index=0;
            _cap=0;
        }
    private:
        size_t _cap;
        std::vector<T> _v;
        //pthread_mutex_t lock;
        sem_t sem_blank;
        sem_t sem_data;
        size_t p_index;
        size_t c_index;
    };
}




#endif
