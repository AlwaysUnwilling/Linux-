#include"tcpServer.h"


int main()
{
  tcpServer* ts=tcpServer::GetInstant();
  ts->tcpServerInit();
  ts->Start();
  return 0;
}
