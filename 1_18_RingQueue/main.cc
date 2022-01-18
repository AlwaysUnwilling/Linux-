#include"ringqueue.hpp"



void* RoutineProductor(void* arg)
{
    my_RingQueue::RingQueue<int>* rq=(my_RingQueue::RingQueue<int>*)arg;
    while(1){
        int data=rand()%10+1;
        rq->Push(data);
        std::cout<<"Productor Push data:"<<data<<std::endl;
        sleep(1);
    }  
}
void* RoutineConsumer(void* arg)
{
    my_RingQueue::RingQueue<int>* rq=(my_RingQueue::RingQueue<int>*)arg;
    while(1){
        int data=0;
        rq->Get(data);
        std::cout<<"Consumer Get data:"<<data<<std::endl;
    } 
}
int main()
{
    pthread_t c,p;
    my_RingQueue::RingQueue<int> rq;
    pthread_create(&c,nullptr,RoutineProductor,&rq);
    pthread_create(&p,nullptr,RoutineConsumer,&rq);

    pthread_join(c,nullptr);
    pthread_join(p,nullptr);
    return 0;
}
