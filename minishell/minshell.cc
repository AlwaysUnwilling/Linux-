#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 256
#define NUM 16

int main()
{
    char cmd[SIZE];
    const char* cmd_line="[Lg@iZwz90afv584hbpk7jhpkuZ minishell]$ ";
    while(1){
        cmd[0]=0;
        printf("%s",cmd_line);
        fgets(cmd,SIZE,stdin);
        printf("%s",cmd);
        cmd[strlen(cmd)-1]='\0';
        char* args[NUM];
        args[0]=strtok(cmd," ");
        int i=1;
        do{
            args[i]=strtok(NULL," ");
            if(args[i]==NULL){
                break;
            }
            ++i;
        }while(1);

         int j=0;
        for(;j<i;++j){
            printf("args[%d]:%s\n",j,args[j]);
        }


        pid_t id=fork();
        if(id<0){
            perror("fork error\n");
            continue;
        }
        if(id==0){
            //child
            execvp(args[0],args);
            exit(1);
        }
        int status=0;
        pid_t ret=waitpid(id,&status,0);
        if(ret>0){
            printf("status code:%d\n",(status>>8)&0xff);
        }
    }
    return 0;
}
