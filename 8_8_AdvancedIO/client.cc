#include"selectClient.h"
#include<memory>


void Usage(std::string str)
{
  std::cout<<"Usage: \t\n"<<"./"<<str<<" IP Port"<<std::endl;
}
int main(int argc,char* argv[])
{
  if(argc!=3){
    Usage(argv[0]);
    exit(9);
  }
  selectClient* sc=new selectClient(argv[1],atoi(argv[2]));
  std::shared_ptr<selectClient> sp(sc);
  sp->selectClientInit();
  sp->Run();
  return 0;
}
