#include"ringqueue.hpp"




void* comsumer(void* ring_queue)
{
    RingQueue* rq=(RingQueue*)ring_queue;
    while(true){
        int data=0;rq->Get(data);
        std::cout<<"comsumer done ... #"<<data<<std::endl;
    }
}
void* productor(void* ring_queue)
{
    RingQueue* rq=(RingQueue*)ring_queue;
    int count=100;
    while(true){
        rq->Put(count);
        count++;
        if(count>110){
            count=100;
        }
        std::cout<<"productor done ... #"<<std::endl;
    }
}
int main()
{
    pthread_t c,p;
    RingQueue* rq=new RingQueue();
    pthread_create(&c,nullptr,comsumer,rq);
    pthread_create(&p,nullptr,productor,rq);

    pthread_join(c,nullptr);
    pthread_join(p,nullptr);
    delete rq;
    return 0;
}
