#ifndef A8170B66_3DC5_4EED_BC0D_A1724CD3199B
#define A8170B66_3DC5_4EED_BC0D_A1724CD3199B

#include<iostream>
#include<unistd.h>
#include<string>
#include<queue>
#include<pthread.h>

namespace my_BlcokQueue
{
    const size_t CAPACITY=5;
    template<typename T>
    class BlockQueue
    {
    private:
        size_t _capacity;
        std::queue<T> _blcokQueue;
        pthread_cond_t p_cond;
        pthread_cond_t c_cond;
        pthread_mutex_t _lock;
    private:
        void LockBlockQueue()
        {
            pthread_mutex_lock(&_lock);
        }
        void UnlockBlockQueue()
        {
            pthread_mutex_unlock(&_lock);
        }
        void WakeUpProcductor()
        {
            pthread_cond_signal(&p_cond);
        }
        void WakeUpConsumer()
        {
            pthread_cond_signal(&c_cond);
        }
        bool IsBlockQueueFull()
        {
            return _blcokQueue.size()==_capacity;
        }
        bool IsBlockQueueEmpty()
        {
            return _blcokQueue.empty();
        }
        void ProductorBlock()
        {
            pthread_cond_wait(&p_cond,&_lock);
        }
        void ConsumerBlock()
        {
            pthread_cond_wait(&c_cond,&_lock);
        }

    public:
        BlockQueue(size_t capacity=CAPACITY)
            :_capacity(capacity)
        {}
        void BlockQueueInit()
        {
            pthread_mutex_init(&_lock,nullptr);
            pthread_cond_init(&p_cond,nullptr);
            pthread_cond_init(&c_cond,nullptr);
        }
        void Push(const T& in_task)
        {
            LockBlockQueue();
            while(IsBlockQueueFull()){
                ProductorBlock();
            }
            _blcokQueue.push(in_task);
            UnlockBlockQueue();
            WakeUpConsumer();
            // while(!IsBlockQueueFull()){
            //     //not full
            //     _blcokQueue.push(in_task);
            // }
            // //full
            // WakeUpConsumer();
            // ProductorBlock();
        }
        void Pop(T& out_task)
        {
            LockBlockQueue();
            while(IsBlockQueueEmpty()){
                ConsumerBlock();
            }
            out_task=_blcokQueue.front();
            _blcokQueue.pop();
            UnlockBlockQueue();
            WakeUpProcductor();
            // while(!IsBlcokQueueEmpty()){
            //     //not empty
            //     out_task=_blcokQueue.front();
            //     _blcokQueue.pop();
            // }
            // //empty
            // WakeUpProcductor();
            // ConsumerBlock();
        }
        ~BlockQueue()
        {
            pthread_mutex_destroy(&_lock);
            pthread_cond_destroy(&p_cond);
            pthread_cond_destroy(&c_cond);
        }
    };
}

#endif /* A8170B66_3DC5_4EED_BC0D_A1724CD3199B */
