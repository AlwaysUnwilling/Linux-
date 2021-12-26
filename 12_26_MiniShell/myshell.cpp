#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

#define NUM 16
#define SIZE 256



int main()
{
    char cmd[SIZE]={0};
    while(1){
        printf("\n[hello:user@Lg520]#");
        fgets(cmd,SIZE,stdin); 
        cmd[strlen(cmd)-1]='\0';
        char* arr[NUM]={0};
        arr[0]=strtok(cmd," ");
        int i=1;
        while(1){
            arr[i]=strtok(NULL," ");
            if(arr[i]==NULL){
                break;
            }
            ++i;
        }
        pid_t id=fork();
        if(id<0){
            perror("fork error!\n");
            continue;
        }else if(id==0){
            execvp(arr[0],arr);
            exit(-1);
        }

        int status=0;
        pid_t ret=waitpid(id,&status,0);
        if(ret>0){
            printf("status:%d\n",(status>>8)&0xff);
        }else{
            perror("waitpid fail!\n");
        }
    }
    return 0;
}
