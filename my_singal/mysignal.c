#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void show_pending(sigset_t* pending)
{
    int sig=1;
    for(;sig<=31;sig++){
        if(sigismember(pending,sig)){
            printf("1");
        }
        else{
            printf("0");
        }
    }
    printf("\n");
}
void handler(int signo)
{
    printf("get a sig:%d\n",signo);
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
    while(1){
        sigemptyset(&pending);
        sigpending(&pending);
        show_pending(&pending);
        sleep(1);
        count++;
        if(count==20){
            printf("recover sig mask!\n");
            sigprocmask(SIG_SETMASK,&oblock,NULL);
        }
    }
    return 0;
}
