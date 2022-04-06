#include "epollServer.hpp"




int main()
{
  epollServer* es=epollServer::GetInstant();
  es->epollServerInit();
  es->start();
  return 0;
}
