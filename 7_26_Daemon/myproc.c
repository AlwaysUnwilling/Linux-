#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

// int daemon(int nochdir, int noclose);//设置守护进程，nochdir--是否需要修改当前路径选项
//                                                      noclose--是否需要屏蔽终端设备---显示器、键盘等

int main()
{
  umask(0);
  if(fork()>0){
    //father proc
    exit(0);
  }
  setsid();//只能是非组长调用该函数---PGRP   ---ps -o pid,ppid,pgrp,session,tpgid,comm
  //调用此函数成功后，此时的子进程已经是一个独立会话---以守护进程的方式进行(也是孤儿进程)。
  //此时的子进程是自成回话，也是该回话的手进程，而会话首进程是有权限打开终端的。如果不需要
  //该会话打开终端的权限，也可再次fork()，然后再把该进程退出，此时剩下的子进程就不是话首进程
  //也就没有打开终端的权限了
  if(fork()>0){ //该步骤非必须，是一种防御型编程，防止有人依靠次权限打开终端进而影响该守护进程。
    //father 
    exit(0);
  }

  //chdir(const char* path);  //修改守护进程的当前路径--不设置的话当前路径就是该进程所在的当前路径
  chdir("/");  //将守护进程的当前路径设置为根目录"/"   仅仅是一个可选项---非必须设置

  //另外一般我们的守护进程都已经和终端(鼠标、键盘)去关联了(已经是一个独立的会话了),不应该再与键盘鼠标显示器等
  //有任何瓜葛了---不需要IO了。但是这里的守护进程打开的IO文件依然是0,1,2对应的设备依然与该设备的终端显示器等
  //关联。
  //linux下有一个字符文件、设备 "/dev/null" ---如果所有输出数据网该设备输入，相当于直接丢弃！而想从该设备中
  //读取内容也是徒劳的---不会读取到任何内容；因此该设备通常用来屏蔽、drop、输入、输出信息
  //
  ////可选项---非必须
  close(0);
  int fd =open("/dev/null",O_RDWR);
  if(fd<0){
    return 1;  //open error
  }
  dup2(fd,1);
  dup2(fd,2);
  while(1);
  return 0;
}
