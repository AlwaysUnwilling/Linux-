#include"udpServer.h"


int main()
{
  udpServer* us=udpServer::GetInstant();
  us->udpServerInit();
  us->Start();
  return 0;
}
