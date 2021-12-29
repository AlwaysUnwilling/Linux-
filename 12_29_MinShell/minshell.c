#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>

#define NUM 128
#define SIZE 16


void redirect(char* getcmd)
{
    char* str=getcmd;
    int red_count=0;
    int fd=-1;
    char* file=NULL;
    while(*str){
        if(*str=='>'){
            *str='\0';
            str++;
            red_count++;
            if(*str=='>'){
                *str='\0';
                str++;
                red_count++;
            }
            while(*str!='\0' && isspace(*str)){
                str++;  
            }
            file=str;
            while(*str!='\0' && !isspace(*str)){
                str++; 
            }
            *str='\0';   
            if(red_count==1){
                //">"
                fd=open(file,O_CREAT|O_TRUNC|O_WRONLY,0644);
            }else{
                //">>"  
                fd=open(file,O_CREAT|O_APPEND|O_WRONLY,0644);
            }
            dup2(fd,1);
            close(fd);
        }
        str++;
    }
}
int main()
{
    char getcmd[NUM]={0};
    while(1){
        printf("[Test@iZwz90 Linux -]$");
        fgets(getcmd,NUM,stdin);
        getcmd[strlen(getcmd)-1]='\0';
        pid_t pid=fork();
        if(pid<0){
            perror("fork fail!\n");
            exit(-1);
        }else if(pid==0){
            redirect(getcmd);
            char* cmd[SIZE]={0};
            cmd[0]=strtok(getcmd," ");
            int i=1;
            while(1){
                cmd[i]=strtok(NULL," "); 
                if(cmd[i]==NULL){
                    break; 
                }
                ++i;
            }
            execvp(cmd[0],cmd);     
        }
        int status=0;
        pid_t ret=waitpid(pid,&status,0);
        if(ret<0){
            perror("waitpid fail!\n");
            exit(-1);
        }else{
            printf("status:%d\n",(status>>8)&0xff);
        }
    }
    return 0;
}
