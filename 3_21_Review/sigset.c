#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>



void show_pending(sigset_t* pending)
{
  for(int i=1;i<32;++i)
  {
    if(sigismember(pending,i))
    {
      printf("1");
    }
    else
    {
      printf("0");
    }
  }
  printf("\n");
}
void handler(int signum)
{
  printf("get a signal:%d\n",signum);
}
int main()
{
  signal(2,handler);
  sigset_t pending;
  sigset_t block,oblock;
  sigemptyset(&block);
  sigemptyset(&oblock);
  sigaddset(&block,2);
  sigprocmask(SIG_SETMASK,&block,&oblock);
  int count=0;
  while(1)
  {
    sigemptyset(&pending);
    sigpending(&pending);
    show_pending(&pending);
    sleep(1);
    if(count>=10)
    {
      sigprocmask(SIG_SETMASK,&oblock,NULL);
    }
    ++count;
  }

  return 0;
}
