#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include<iostream>
#include<queue>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>

#define NUM 5

namespace my_PthreadPool
{
    template<class T>
    class Task
    {
    public:
        Task(){}
        Task(int b)
        :_base(b)
        {}
        void Run()
        {
           std::cout<<"Pthread ID is:["<<pthread_self()<<"] Task result:"<<_base<<" pow(base,2):"<<pow(_base,2)<<std::endl;   
        }
    private:
        int _base;
    };
    
    template<class T>
    class PthreadPool
    {
    public:
        bool IsEmpty()
        {
            return _q.empty(); 
        }
        void LockQueue()
        {
            pthread_mutex_lock(&_lock);
        }
        void UnlockQueue()
        {
            pthread_mutex_unlock(&_lock);
        }
        void PthreadWait()
        {
            pthread_cond_wait(&_cond,&_lock);
        }
        void PthreadWakeUp()
        {
            pthread_cond_signal(&_cond);
        }
        static void* Routine(void* arg)
        {
            PthreadPool* this_p=(PthreadPool*)arg;
            while(1){
                this_p->LockQueue();
                while(this_p->IsEmpty()){
                    this_p->PthreadWait();
                }
                Task<T> t;
                this_p->Get(t);
                this_p->UnlockQueue();
                t.Run();     //处理任务可以在临界区外
            }
        }
        void PthreadPoolInit()
        {
            pthread_mutex_init(&_lock,nullptr);
            pthread_cond_init(&_cond,nullptr);
            pthread_t pt;
            for(size_t i=0;i<_cap;++i){
                pthread_create(&pt,nullptr,Routine,this);
            }
        }
    public:
        PthreadPool(int cap=NUM)
        :_cap(cap)
        {
            PthreadPoolInit();
        }
        void Push(Task<T>& t)   //server
        {
            LockQueue();
            _q.push(&t);
            UnlockQueue();
            PthreadWakeUp();
        }
        void Get(Task<T>& t)    //pthread pool pthread
        {
            Task<T>* tmp=_q.front();
            _q.pop();
            t=*tmp;
        }              
        ~PthreadPool()
        {
            pthread_mutex_destroy(&_lock);
            pthread_cond_destroy(&_cond);
            _cap=0;
        }
    private:
        std::queue<Task<T>*> _q;
        size_t _cap;
        pthread_mutex_t _lock;
        pthread_cond_t _cond;   //only consumer,thread pool thread;
    };
}





#endif
