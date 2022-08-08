#include"selectServer.h"
#include<memory>

int main()
{
  selectServer* ssver=selectServer::GetInstance();
  std::shared_ptr<selectServer> sp(ssver);
  sp->Run();
  return 0;
}
