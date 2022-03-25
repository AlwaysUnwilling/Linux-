#include"ThreadPool.h"


void Task::Run()
{
  char request[1024];
  ssize_t s=recv(sock,request,sizeof(request)-1,0);  //bug:实际场景中需要循环读取，知道读取到一个完整的请求
  if(s>0){
    request[s]=0;
    std::cout<<"[Client: ]"<<request<<std::endl;
    std::string response="HTTP/1.0 200 OK\r\n";
    response+="Content-type: text/html\r\n";
    response+="\r\n";
    response+="\
      <!DOCTYPE html>\
      <html>\
      <head>\
      <title>Welcome To MyZone</title>\
      </head>\
      <body>\
      <h1>Welcome</h1>\
      <p>Welcome to my first web page!</p>\
      </body>\
      </html>\
      ";
    if(send(sock,response.c_str(),response.size(),0)<0){
      std::cout<<"send error!"<<std::endl;
    }
  }else if(s==0){
    std::cout<<"Client quit!"<<std::endl;
  }else{
    std::cout<<"recv error!"<<std::endl;
  }
  close(sock);
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
