#ifndef __BLOCKQUEUE_H__
#define __BLOCKQUEUE_H__

#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<queue>

namespace my_blockqueue
{
    template<class T>
    class BlockQueue
    {
    public:
        bool IsFull()
        {
            return _q.size()==_cap;
        }
        bool IsEmpty()
        {
            return _q.empty();
        }
        void QueueLock()
        {
            pthread_mutex_lock(&lock);
        }
        void QueueUnlock()
        {
            pthread_mutex_unlock(&lock);
        }
        void ConsumerWakeUp()
        {
            pthread_cond_signal(&c_cond); 
        }
        void ConsumersWait()
        {
            pthread_cond_wait(&c_cond,&lock); 
        }
        void ProducerWait()
        {
            pthread_cond_wait(&p_cond,&lock);
        }
        void ProducerWakeUp()
        {
            pthread_cond_signal(&p_cond);   
        }
    public:
        BlockQueue(size_t cap=5)
        :_cap(cap)
        {
            pthread_mutex_init(&lock,nullptr);
            pthread_cond_init(&p_cond,nullptr);
            pthread_cond_init(&c_cond,nullptr);
        }

        void Push(const T& data)
        {
            QueueLock();
            while(IsFull()){            //防止异常唤醒，所以使用while来循环判断队列是否为满
                ConsumerWakeUp();       //单纯的使用if判断可能会造成因为异常唤醒而带来的bug
                ProducerWait();
            }
            _q.push(data); 
            QueueUnlock();
        }

        void Get(T& data)
        {
            QueueLock();
            while(IsEmpty()){           //防止异常唤醒，所以使用while来循环判断队列是否为空
                ProducerWakeUp();
                ConsumersWait();
            }
            data=_q.front();
            _q.pop();
            QueueUnlock();
        }
        ~BlockQueue()
        {
            _cap=0;
            pthread_mutex_destroy(&lock);
            pthread_cond_destroy(&p_cond);
            pthread_cond_destroy(&c_cond);
        }
    private:
        std::queue<T> _q;
        size_t _cap;
        pthread_mutex_t lock;
        pthread_cond_t p_cond;   //The producer waits under this condition.
        pthread_cond_t c_cond;   //Consumers wait under this condition.
    };
}






#endif
