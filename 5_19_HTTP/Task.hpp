#pragma once 

#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include"Protocol.hpp"

class Task
{
  private:
    int sock;
    CallBack HandlerTask;  //设置回调---仿函数
  public:
    Task()
    {}
    Task(int _sock)
      :sock(_sock)
    {}
    void ProcessOn()
    {
      HandlerTask(sock);
    }
    ~Task()
    {}
};
