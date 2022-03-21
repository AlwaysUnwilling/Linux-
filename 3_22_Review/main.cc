#include"RingQueue.hpp"

#define NUM 5


pthread_mutex_t pro_lock;
pthread_mutex_t com_lock;



void* Pro_Thread_Run(void* arg)
{
  RingQueue<int>* rq=(RingQueue<int>*)arg;
  int data=0;
  while(true)
  {
    pthread_mutex_lock(&pro_lock);
    data=rand()%100;
    rq->Put(data);
    pthread_mutex_unlock(&pro_lock);
    std::cout<<"Productor: "<<pthread_self()<<" Put data: "<<data<<std::endl;
    sleep(1);
  }
}
void* Com_Thread_Run(void* arg)
{
  RingQueue<int>* rq=(RingQueue<int>*)arg;
  int data=0;
  while(true)
  {
    pthread_mutex_lock(&com_lock);
    rq->Get(data);
    pthread_mutex_unlock(&com_lock);
    std::cout<<"Comsumer: "<<pthread_self()<<" Get data: "<<data<<std::endl; 
    sleep(1);
  }
}
int main()
{
  pthread_mutex_init(&pro_lock,nullptr);
  pthread_mutex_init(&com_lock,nullptr);
  pthread_t p[NUM],c[NUM];
  RingQueue<int> rq(10);
  for(size_t i=0;i<NUM;++i)
  {
    pthread_create(p+i,nullptr,Pro_Thread_Run,(void*)&rq);
    pthread_create(c+i,nullptr,Com_Thread_Run,(void*)&rq);
  }

  for(size_t i=0;i<NUM;++i)
  {
    pthread_join(p[i],nullptr);
    pthread_join(c[i],nullptr);
  }
  pthread_mutex_destroy(&pro_lock);
  pthread_mutex_destroy(&com_lock);
  return 0;
}
