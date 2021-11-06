#ifndef __QUEUE_BlOCK_H__
#define __QUEUE_BlOCK_H__
#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<queue>
class BlcokQueue{
public:
    bool IsFull()
    {
        return q.size()>=cap;
    }
    bool IsEmpty()
    {
        return q.empty();
    }
    void LockQueue()
    {
        pthread_mutex_lock(&lock);
    }
    void UnLockQueue()
    {
        pthread_mutex_unlock(&lock);
    }
    void WakeUpCustomer()
    {
        //pthread_cond_broadcast(&c_cond);
        pthread_cond_signal(&c_cond);
    }
    void ProductorWait()
    {
        pthread_cond_wait(&p_cond,&lock);
    }
    void WakeUpProductor()
    {
        //pthread_cond_broadcast(&p_cond);
        pthread_cond_signal(&p_cond);
    }
    void CustomerWait()
    {    
        pthread_cond_wait(&c_cond,&lock);
    }
public:
    BlcokQueue(size_t _cap):cap(_cap)
    {
        pthread_mutex_init(&lock,nullptr);
        pthread_cond_init(&c_cond,nullptr);
        pthread_cond_init(&p_cond,nullptr);
    }
    void Put(int in)
    {
        LockQueue();
        while(IsFull()){
            WakeUpCustomer();
            ProductorWait();
        }
        q.push(in);
        UnLockQueue();
    }
    void Get(int& out)
    {
        LockQueue();
        while(IsEmpty()){
            WakeUpProductor();
            CustomerWait();
        }
        out=q.front();
        q.pop();
        UnLockQueue();

    }

    ~BlcokQueue()
    {
        pthread_mutex_destroy(&lock);
        pthread_cond_destroy(&c_cond);
        pthread_cond_destroy(&p_cond);
    }
private:
    std::queue<int> q;
    size_t cap;
    pthread_mutex_t lock;
    pthread_cond_t c_cond;//消费者在该条件变量下等
    pthread_cond_t p_cond;//生产者在该条件变量下等
};


#endif
