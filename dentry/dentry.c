#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int a=1,b=1;

int test()
{
    a++;
    sleep(5);
    b++;
    return a+b;
}
void sigcb(int signo)
{
    printf("signal sum:%d\n",test());
}
int main()
{
    signal(SIGINT,sigcb);
    printf("main sum:%d\n",test());
    return 0;
}
