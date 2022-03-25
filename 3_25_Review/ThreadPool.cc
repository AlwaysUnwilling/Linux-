#include"ThreadPool.h"


void Task::Run()
{
  request_t rq;
  response_t rp;
  ssize_t s=recv(sock,&rq,sizeof(rq),0);
  if(s>0){
    switch(rq.op){
      case '+':
        rp.result=rq.x+rq.y;
        rp.code=0;
        break;
      case '-':
        rp.result=rq.x-rq.y;
        rp.code=0;
        break;
      case '*':
        rp.result=rq.x*rq.y;
        rp.code=0;
        break;
      case '/':
        if(rq.y==0){
          rp.code=1;
          rp.result=-1;
        }else{
          rp.code=0;
          rp.result=rq.x/rq.y;
        }
        break;
      case '%':
        if(rq.y==0){
          rp.code=1;
          rp.result=-1;
        }else{
          rp.result=rq.x%rq.y;
          rp.code=0;
        }
        break;
      default:
        rp.code=2;
        rp.result=-2;
        break;
    }
    if(send(sock,&rp,sizeof(rp),0)<0){
      std::cerr<<"send error!"<<std::endl;
    }
  }else if(s==0){
    std::cout<<"Client quit!"<<std::endl;
  }else{
    std::cerr<<"recv error!"<<std::endl;
  }
}

ThreadPool ThreadPool::obj;

void* ThreadPool:: Routine(void* arg)
{
  ThreadPool* pthis=(ThreadPool*)arg;
  pthis->LockQueue();
  Task* t=new Task;
  while(pthis->IsEmpty()){
    pthis->ThreadWait();
  }
  pthis->Get(t);
  pthis->UnlockQueue();
  t->Run();
  delete t;
  return nullptr;
}
void ThreadPool::ThreadPoolInit()
{
  pthread_mutex_init(&lock,nullptr); 
  pthread_cond_init(&cond,nullptr); 
  pthread_t pt[NUM];
  for(size_t i=0;i<NUM;++i){
    pthread_create(pt+i,nullptr,Routine,(void*)this);
  }
}
void ThreadPool::LockQueue()
{
  pthread_mutex_lock(&lock);
}
void ThreadPool::UnlockQueue()
{
  pthread_mutex_unlock(&lock);
}
bool ThreadPool::IsFull()
{
  return q.size()==max_cap;
}
bool ThreadPool::IsEmpty()
{
  return q.empty();
}
void ThreadPool:: WakeUpThread()
{
  pthread_cond_signal(&cond);
}
void ThreadPool::ThreadWait()
{
  pthread_cond_wait(&cond,&lock);
}
void ThreadPool::Put(Task* t)
{
  LockQueue();
  q.push(t);
  WakeUpThread();
  UnlockQueue();
}
void ThreadPool::Get(Task*& t)
{
  t=q.front();
  q.pop();
}
