#include"tcpClient.h"


void Manual(std::string str)
{
  std::cout<<"Manual:\n\t";
  std::cout<<str<<" IP Port"<<std::endl;
}
int main(int argc, char*argv[])
{
  if(argc!=3){
    Manual(argv[0]);
    exit(9);
  }
  tcpClient* tc=new tcpClient(argv[1],atoi(argv[2]));
  tc->tcpClientInit();
  tc->Start();
  return 0;
}
