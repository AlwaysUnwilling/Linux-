#include<iostream>
#include<stdio.h>
#include<string>
#include<cstring>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

const size_t NUM=15;

int main()
{
  std::string prompt{"[temp@centos7_bash]# "};
  while(true)
  {
    std::cout<<prompt;
    char cmd[256]={0};
    fgets(cmd,256,stdin);
    cmd[strlen(cmd)-1]=0;
    char* cmdArr[NUM]={0};
    cmdArr[0]=strtok(cmd," ");
    size_t index=1;
    while(cmdArr[index-1]){
      cmdArr[index]=strtok(NULL," ");
      ++index;
    }
    cmdArr[index]=NULL;
    pid_t pid=fork();
    if(pid<0){
      std::cerr<<"fork error!"<<std::endl;
      exit(1);
    }
    if(pid==0){
      execvp(cmdArr[0],cmdArr);
      exit(2);
    }
    int status=0;
    pid_t child=waitpid(pid,&status,0);
    if(child>0){
      if((status&0x7f)==0){
        std::cout<<"exit code:"<<((status>>8)&0xff)<<std::endl;
      }
      else{
        std::cout<<"exit signal:"<<(status&0x7f)<<std::endl;
      }
    }
  }
  return 0;
}
