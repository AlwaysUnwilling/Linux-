#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>


#define SIZE 128


void ParseStr(char* str);
void CheckStr(char* buff)
{
  int count=0;
  char* str=buff;
  while(*str!=0)
  {
    if(*str=='>') // ">"
    {
      *str=0;
      count++;
      ++str;
      if(*str=='>') // ">>"
      {
        ++count;
        *str=0;
        ++str;
      }
      //file name
      while(*str!=0 &&  isspace(*str))
      {
        ++str;
      }
      char* file=str;
      while(*str!=0 && !isspace(*str))
      {
        ++str;
      }
      *str=0;
      int fd=-1;
      if(count==1)
      {
        fd=open(file,O_CREAT |O_TRUNC | O_RDWR,0777);
      }
      if(count==2){
        fd=open(file,O_CREAT |O_APPEND | O_RDWR,0777);
      }
      if(fd<0)
      {
        perror("open error!\n");
        exit(1);
      }
      dup2(fd,1);
      ParseStr(buff);
      close(fd);
      break;
    }
    ++str;
  }
}
void ParseStr(char* str)
{
  printf("%s",str);
  char* cmd[SIZE]={0};
  size_t i=1;
  while(isspace(*str))
  {
    ++str;
  }
  cmd[0]=strtok(str," ");
  while(cmd[i-1])
  {
    cmd[i++]=strtok(NULL," ");
  }
  cmd[i]=NULL;
  execvp(cmd[0],cmd);
}
void MinShell()
{
  const char* shellPrompt="[MinShell@client_msg]# ";
  size_t num=0;
  while(1)
  {
    char* buff=NULL;
    printf("%s",shellPrompt);
    ssize_t s=getline(&buff,&num,stdin);
    if(s<0)
    {
      perror("getline error!\n");
      continue;
    }
    buff[s-1]=0;
    pid_t pid=fork();
    if(pid<0)
    {
      perror("fork error!\n");
      continue;
    }
    else if(pid==0)
    {
      CheckStr(buff);
      free(buff);
      exit(0);
    }
    int status=0;
    pid_t child=waitpid(pid,&status,0);
    if(child>0)
    {
      printf("exit code:%d\n",(status>>8)&0xff);
    }
    else
    {
      perror("wait fail!\n");
    }
  }
}
int main()
{
  MinShell();  
  return 0;
}
