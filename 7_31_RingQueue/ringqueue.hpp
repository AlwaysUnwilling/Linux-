#ifndef D13C064C_F837_40C0_8701_3D9CD3EB7CF9
#define D13C064C_F837_40C0_8701_3D9CD3EB7CF9

#include<iostream>
#include<vector>
#include<unistd.h>
#include<semaphore.h>

namespace my_Semaphore
{
    const size_t CAP=5;
    template<typename T>
    class RingQueue
    {
    private:
        size_t cap;
        std::vector<T> rq;
        size_t c_index;
        size_t p_index;
        sem_t sem_blank;
        sem_t sem_data;
    private:
        void P(sem_t& semVal)
        {
            sem_wait(&semVal);
        }
        void V(sem_t& semVal)
        {
            sem_post(&semVal);
        }
    public:
        RingQueue(size_t _cap=CAP)
        :cap(_cap),c_index(0),p_index(0),rq(cap,T())
        {}
        void RingQueueInit()
        {
            sem_init(&sem_blank,0,cap);
            sem_init(&sem_data,0,0);
        }
        void Push(const T& inTask)
        {
            P(sem_blank);
            rq[p_index]=inTask;
            V(sem_data);
            p_index++;
            p_index %= cap;
        }
        void Pop(T& outTask)
        {
            P(sem_data);
            outTask=rq[c_index];
            V(sem_blank);
            c_index++;
            c_index %= cap;
        }
        ~RingQueue()
        {
            sem_destroy(&sem_blank);
            sem_destroy(&sem_data);
        }
    };
}

#endif /* D13C064C_F837_40C0_8701_3D9CD3EB7CF9 */
