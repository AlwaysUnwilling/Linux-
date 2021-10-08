#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#define SIZE 256
#define NUM 16

void redirect(char* cmd){
    char* ptr=cmd;
    int fd =-1;
    int redirect_count=0;
    char *file=NULL;
    while(*ptr){
        if(*ptr=='>'){
            *ptr++='\0';
            redirect_count++;
            if(*ptr=='>'){
                *ptr++='\0';
                redirect_count++;
            }
            while(*ptr!='\0' && isspace(*ptr)){
                ptr++;
            }
            file=ptr;
            while(*ptr!='\0' && !isspace(*ptr)){
                ptr++;
            }
            *ptr='\0';
            if(redirect_count==1){
               fd=open(file,O_CREAT | O_TRUNC | O_WRONLY,0644);
                if(fd<0){
                    perror("open error\n");
                }
            }else if(redirect_count==2){
               
               fd=open(file,O_CREAT | O_APPEND | O_WRONLY,0644); 
            }else{
               ;
            }

            dup2(fd,1);
            close(fd);
        }
        ptr++;
    }
}
int main()
{
    char cmd[SIZE];
    const char* cmd_line="[minishell@iZwz90afv584hbpk7jhpkuZ minishell]$ ";
    while(1){
        cmd[0]=0;
        printf("%s",cmd_line);
        fgets(cmd,SIZE,stdin);
        printf("%s",cmd);
        cmd[strlen(cmd)-1]='\0';
        pid_t id=fork();
        if(id<0){
            perror("fork error\n");
            continue;
        }
        if(id==0){
            //child

            redirect(cmd);
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
