#include"selectServer.hpp"



int main()
{
  selectServer* ss=selectServer::GetInstant();
  ss->selectServerInit();
  ss->Start();
  return 0;
}
