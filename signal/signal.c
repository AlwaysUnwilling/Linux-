#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

void sigcb(int signo)
{
    printf("recv a signal no:%d\n",signo); 
}
int main()
{
    //signal(SIGINT,SIG_IGN);
    //当信号到来时才会调用sigcb这个函数，并且通过参数传入当前触发回调函数的信号值
    signal(SIGINT,sigcb);//该函数并非阻塞状态，只是当信号到来时才会调用该函数
    while(1){
        printf("刚才的雷阵雨好大~~\n");
        sleep(10);
    }
    return 0;
}
