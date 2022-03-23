#include"udpClient.h"

int main()
{
  udpClient* uc=udpClient::GetInstant();
  uc->udpClientInit();
  uc->Start();
  return 0;
}
