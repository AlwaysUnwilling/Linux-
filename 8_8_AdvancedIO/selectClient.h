#pragma once 

#include<iostream>
#include<unistd.h>
#include"sock.hpp"
#include<string>

class selectClient
{
private:
  int port;
  int sock;
  std::string ip;
public:
  selectClient(std::string _ip,int _port);
  void selectClientInit();
  void Run();
  ~selectClient();
};
