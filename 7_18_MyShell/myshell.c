#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

void ParserCmd(char* cmd,char*cmdList[])
{
    if(cmd==NULL){
        printf("cmd error!\n");
        exit(3);
    }
    int i=0;
    char* str=strtok(cmd," ");
    cmdList[i++]=str;
    while(1){
        char* str=strtok(NULL," ");
        if(str==NULL){
            break;
        }
        //printf("%s\n",str);
        cmdList[i++]=str;
    }
}
int main()
{
    const char* hostName="[Lg@CentOs7_7_18_MyShell]$ ";
    while(1){
        printf("%s",hostName);
        char cmd[1024]={0};
        fflush(stdout);
        fgets(cmd,1024,stdin);
        cmd[strlen(cmd)-1]='\0';
        //printf("%s\n",cmd);
        char* cmdList[10]={NULL};
        ParserCmd(cmd,cmdList);
        // for(int i=0;i<10;++i){
        //     if(cmdList[i]==NULL){
        //         break;
        //     }
        //     printf("%s\n",cmdList[i]);
        // }
        pid_t pid=fork();
        if(pid<0){
            printf("fork error!\n");
            exit(1);
        }else if(pid==0){
            //child execv();
            execvp(cmdList[0],cmdList);
            printf("execv() error!\n");
            exit(2);
        }
        int status=0;
        int ret=waitpid(pid,&status,0);
        if(ret>0){
            printf("exit code:%d\n",WEXITSTATUS(status));
        }
    }
    return 0;
}