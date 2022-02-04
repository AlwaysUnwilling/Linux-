#include"tcpclientMp.hpp"

void Usage(char* argv)
{
    std::cout<<"Usage:\t";
    std::cout<<"./"<<argv<<" IP Port"<<std::endl;
}
int main(int argc,char* argv[])
{
    if(argc!=3){
        Usage(argv[0]);
        exit(1);
    }
    TcpClientMp tcm(argv[1],atoi(argv[2]));
    tcm.TcpClientMpInit();
    tcm.Start();
    return 0;
}
