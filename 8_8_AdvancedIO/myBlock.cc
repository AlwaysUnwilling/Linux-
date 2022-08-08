#include<iostream>
#include<string>
#include<unistd.h>
#include<fcntl.h>


const size_t BUFF_SIZE=1024;

bool SetNoBlock(int fd)
{
  int f1=fcntl(fd,F_GETFL);  //获得文件的标记
  if(f1 < 0){
    std::cerr<<"fcntl fail!"<<std::endl;
    return false;
  }
  fcntl(fd,F_SETFL,f1|O_NONBLOCK);   //设置非阻塞
  return true;
}
int main()
{
  char buff[BUFF_SIZE];
  if(!SetNoBlock(0)){
    std::cout<<"SetNoBlock error!"<<std::endl;
    return 1;
  }
  while(true){
    ssize_t s=read(0,buff,BUFF_SIZE-1);
    if(s < 0){
      //若设置read为非阻塞读取，那么它的返回值<0时不一定是read读取错误了，有可能
      //是底层没有数据而返回(非阻塞读取时，是以出错的形式返回的)
      if(EAGAIN==errno || EWOULDBLOCK==errno){
        std::cout<<"no data readed!"<<std::endl;
        sleep(1);
        continue;
      }else if(EINTR==errno){
        std::cout<<"数据未知，此次读取被信号中断"<<std::endl;
        continue;
      }else{
        std::cerr<<"read error!"<<std::endl;
        break;
      }
    }else if(s==0){
      std::cout<<"fd 0 did not open!"<<std::endl;
    }else{
      buff[s-1]=0;
      std::cout<<"[Read Mesg]# "<<buff<<std::endl;
    }
  }
  return 0;
}

