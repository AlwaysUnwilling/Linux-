#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void handler(int signo)
{
    printf("get a signo:%d\n",signo);
}
int main()
{
    struct sigaction act,oact;
    act.sa_handler=handler;
    act.sa_flags=0;
    sigemptyset(&act.sa_mask);
    sigemptyset(&oact.sa_mask);
    sigaction(2,&act,&oact);
    while(1){
        ;
    }
    return 0;
}
