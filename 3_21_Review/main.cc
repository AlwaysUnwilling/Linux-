#include"BlockQueue.hpp"


pthread_mutex_t plock;
pthread_mutex_t comlock;
void* pthread_comsumer_run(void* arg)
{
  BlockQueue<Task>* bq=(BlockQueue<Task>*)arg;
  while(true){
    Task t(0,0);
    pthread_mutex_lock(&comlock);
    bq->Get(t);
    pthread_mutex_unlock(&comlock);
    std::cout<<"Comsumer:get_tid"<<pthread_self()<<" get data: "<<t.Sum()<<std::endl;
    sleep(1);
  }
}
void* pthread_productor_run(void* arg)
{
  BlockQueue<Task>* bq=(BlockQueue<Task>*)arg;
  while(true){
    Task t(rand()%10,rand()%10);
    pthread_mutex_lock(&plock);
    bq->Put(t);
    pthread_mutex_unlock(&plock);
    std::cout<<"Productor:get_tid: "<<pthread_self()<<" data: "<<t.First()<<"+"<<t.Second()<<"= ?"<<std::endl;
    sleep(3);
  }
}
int main()
{
  pthread_mutex_init(&plock,nullptr);
  pthread_mutex_init(&comlock,nullptr);
  BlockQueue<Task> bq(5);
  pthread_t p[5],c[5];
  for(size_t i=0;i<5;++i)
  {
    pthread_create(p+i,nullptr,pthread_productor_run,(void*)&bq);
  }
  for(size_t i=0;i<5;++i)
  {
    pthread_create(c+i,nullptr,pthread_comsumer_run,(void*)&bq);
  }

  for(size_t i=0;i<5;++i)
  {
    pthread_join(p[i],nullptr);
    pthread_join(c[i],nullptr);
  }
  pthread_mutex_destroy(&plock);
  pthread_mutex_destroy(&comlock);
  return 0;
}
