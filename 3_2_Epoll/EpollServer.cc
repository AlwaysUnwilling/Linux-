#include"EpollServer.hpp"


void Usage(std::string str)
{
    std::cout<<"Usage: \n\t"<<str<<" Port"<<std::endl;
}
int main(int argc,char* argv[])
{
    if(argc!=2){
        Usage(argv[0]);
        exit(4);
    }
    EpollServer* es=new EpollServer(atoi(argv[1]));
    es->EpollServerInit();
    es->Start();
    return 0;
}
