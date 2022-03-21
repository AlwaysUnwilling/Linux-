#include"ThreadPool.hpp"


int main()
{
  ThreadPool* tp=new ThreadPool(5);
  tp->ThreadPoolInit();
  while(true)
  {
    Task t;
    tp->Put(&t);
    sleep(1);
  }
  return 0;
}
