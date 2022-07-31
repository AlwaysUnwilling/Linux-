#ifndef C4202D61_4FCA_4C80_B552_613D840D0E53
#define C4202D61_4FCA_4C80_B552_613D840D0E53

#include<iostream>
#include<pthread.h>
#include<queue>
#include<vector>
#include<functional>
#include<unistd.h>


namespace my_PthreadPool
{
    template<class T1,class T2,class CALCULATE=std::function<void(int,int,char)>>
    class Task
    {
    private:
        T1 x;
        T2 y;
        char op;
        CALCULATE cal;
    private:
        static void mathCal(int data1,int data2,char opSign) throw(const char*)
        {
            switch (opSign)
            {
            case '+':
                std::cout<<data1<<"+"<<data2<<"="<<data1+data2<<std::endl;
                break;
            case '-':
                std::cout<<data1<<"-"<<data2<<"="<<data1-data2<<std::endl;
                break;
            case '*':
                std::cout<<data1<<"*"<<data2<<"="<<data1*data2<<std::endl;
                break;
            case '/':
                if(data2==0){
                    throw "错误请求：除数为0！";
                }else{
                    std::cout<<data1<<"/"<<data2<<"="<<data1/data2<<std::endl;
                }
                break;
            case '%':
                if(data2==0){
                    throw "错误请求：除数为0！";
                }else{
                    std::cout<<data1<<"%"<<data2<<"="<<data1%data2<<std::endl;
                }
                break;                                    
            default:
                std::cout<<"bad requests!"<<std::endl;
                break;
            }
        }
    public:
        Task()
        {}
        Task(T1 _x,T2 _y,char _op,CALCULATE _cal=Task::mathCal)
            :x(_x),y(_y),op(_op),cal(_cal)
            {}
        void Run()
        {
            cal(x,y,op);
        }
    };

    template<typename T,class T1,class T2>
    class PthreadPool
    {
    private:
        size_t thread_size;
        std::queue<T> task_queue;
        pthread_mutex_t lock;
        pthread_cond_t cond;
    private:
        void LockTaskQueue()
        {
            pthread_mutex_lock(&lock);
        }
        void UnlockTaskQueue()
        {
            pthread_mutex_unlock(&lock);
        }
        void PthreadBlock()
        {
            pthread_cond_wait(&cond,&lock);
        }
        void WakeUpPthread()
        {
            pthread_cond_signal(&cond);
        }
        bool IsTaskQueueEmpty()
        {
            return task_queue.empty();
        }
        static void* TaskRoutine(void* arg)
        {
            PthreadPool<T,T1,T2>* self_this=(PthreadPool<T,T1,T2>*)arg;
            while (true){
                /* code */
                self_this->LockTaskQueue();
                while(self_this->IsTaskQueueEmpty()){
                    self_this->PthreadBlock();
                }
                Task<T1,T2> t;
                self_this->Pop(t);
                self_this->UnlockTaskQueue();
                try
                {
                    t.Run();
                }
                catch(const char* err)
                {
                    std::cout<<err<<std::endl;
                }
                
                usleep(1000);
            }
            return nullptr;
        }
    public:
        PthreadPool(int _thread_size=5)
            :thread_size(_thread_size)
            {}
        void PthreadPoolInit()
        {
            pthread_mutex_init(&lock,nullptr);
            pthread_cond_init(&cond,nullptr);
            std::vector<pthread_t> vt(thread_size,pthread_t());
            for(auto& tid:vt){
                pthread_create(&tid,nullptr,TaskRoutine,(void*)this);
            }
        }
        void Push(const T& inTask)
        {
            LockTaskQueue();
            task_queue.push(inTask);
            UnlockTaskQueue();
            WakeUpPthread();
        }
        void Pop(T& outTask)
        {
            outTask=task_queue.front();
            task_queue.pop();
        }
        ~PthreadPool()
        {
            pthread_mutex_destroy(&lock);
            pthread_cond_destroy(&cond);
        }
    };
}

#endif /* C4202D61_4FCA_4C80_B552_613D840D0E53 */
