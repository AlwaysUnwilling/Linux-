#include"tcpserverMp.hpp"
#include<stdlib.h>

void Usage(char* argv)
{
    std::cout<<"Usage\t";
    std::cout<<"./"<<argv<<" "<<"port"<<std::endl;
}
int main(int argc,char* argv[])
{
    if(argc!=2){
        Usage(argv[0]);
        exit(5);
    }
    TcpServerMp tsm(atoi(argv[1]));
    tsm.TcpServerMpInit();
    tsm.Start();
    return 0;
}
