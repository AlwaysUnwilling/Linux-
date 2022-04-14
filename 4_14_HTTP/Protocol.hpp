#pragma once 

#include<iostream>
#include<unistd.h>
#include"Util.hpp"
class Entrance
{
  public:
    static void* HandlerRequest(void* arg)
    {
      int sock=*(int*)arg;
      std::cout<<"get a new link..."<<sock<<std::endl;
      std::string out;
      int status=Util::ReadLine(sock,out);
      if(status>0){
        std::cout<<out<<std::endl;
      }
      delete (int*)arg;
      close(sock);
      return nullptr;
    }
};
