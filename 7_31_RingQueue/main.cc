#include"ringqueue.hpp"
#include<pthread.h>
#include<memory>
#include<cstdlib>


void* ConsumerRoutine(void* arg)
{
    std::shared_ptr<my_Semaphore::RingQueue<int>> sp=*(std::shared_ptr<my_Semaphore::RingQueue<int>>*)arg;
    while(true){
        int task=-1;
        sp->Pop(task);
        std::cout<<"Consumer Taking Task..."<<task<<std::endl;
        sleep(1);
    }
}
void* ProductorRoutine(void* arg)
{
    std::shared_ptr<my_Semaphore::RingQueue<int>> sp=*(std::shared_ptr<my_Semaphore::RingQueue<int>>*)arg;
    while(true){
        int task=rand()%100+1;
        sp->Push(task);
        std::cout<<"Productor Pushing Task..."<<task<<std::endl;
        sleep(1);
    }
}
void TestRingQueue()
{
    my_Semaphore::RingQueue<int>* rq=new my_Semaphore::RingQueue<int>;
    rq->RingQueueInit();
    std::shared_ptr<my_Semaphore::RingQueue<int>> sp(rq);
    auto sp1=sp;
    pthread_t c,p;
    pthread_create(&c,nullptr,ConsumerRoutine,(void*)&sp);
    pthread_create(&p,nullptr,ProductorRoutine,(void*)&sp1);

    pthread_join(c,nullptr);
    pthread_join(p,nullptr);
}
int main()
{   srand(0);
    TestRingQueue();
    return 0;
}