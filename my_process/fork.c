/*===============================================================================
 * Copyright(C).ALL Rights Reserved")
 * 文件名称：
 * 创 建 者：
 * 创建日期：
 * 描    述：这个demo用于体会如何创建一个进程，以及创建的进程的各项细节。
 * ")
 * ============================================================================*/

#include<stdio.h>
#include<unistd.h>

int main()
{
   printf("----------create child process start-------\n");
   pid_t pid;  //定义这个变量只是开辟了一块空间
   pid=fork();  //这个函数的返回值对于父子进程是不一样的
   if(pid>0)
   {
     printf("this is parent--%d--rpid:%d\n",getpid(),pid);  //这是以一个父进程
   }
   else if(pid<0)
   {
     printf("error\n");  //出错了
   }
   else 
   {
     printf("this is child--%d--rpid:%d\n",getpid(),pid); //这是一个子进程
   }

   printf("---------create child process end----------%d--rpid:%d\n",getpid(),pid);
   return 0;
}

