#include<stdio.h>
#include<unistd.h>
#include<signal.h>

//volatile保证cpu每次都从内存中获取数据
volatile long long a=1;
void sigcb(int signo)
{
    a=0;
    printf("a=%d\n",a);
}
int main()
{
    signal(SIGINT,sigcb);
    while(a){
        ;
    }
    printf("exited a= %d\n",a);
    return 0;
}
