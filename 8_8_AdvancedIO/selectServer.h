#ifndef __SELECTSERVER_H__
#define __SELECTSERVER_H__ 

#include<iostream>
#include<string>
#include<unistd.h>
#include<pthread.h>
#include<vector>
#include<sys/select.h>
#include"sock.hpp" 

const int DEF_PORT=8080;
const size_t BACK_LEN=5;
class selectServer 
{
private:
  int port;
  int backlen;
  int lsock;
  static pthread_mutex_t lock;
private:
  static selectServer* refServer;
  selectServer(int _port=DEF_PORT,int _backlen=BACK_LEN);
  void selectServerInit();  
  void HandlerEvents(fd_set& rfds,std::vector<int>& fdArray);
public:
  selectServer& operator=(const selectServer& ss)=delete;
  selectServer(selectServer& ss)=delete;
  static selectServer* GetInstance()
  {
    if(refServer==nullptr){
      pthread_mutex_lock(&lock);
      if(refServer==nullptr){
        refServer=new selectServer();
        if(refServer==nullptr){
          std::cerr<<"GetInstance error!"<<std::endl;
          exit(4);
        }
        refServer->selectServerInit();
      }
      pthread_mutex_unlock(&lock);
    } 
    return refServer;
  }
  void Run();
  ~selectServer();
};

#endif 
