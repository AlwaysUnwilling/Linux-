#include"PollServer.hpp"


void Usage(std::string str)
{
    std::cout<<"Usage: \n\t"<<str<<" Port"<<std::endl;
}
int main(int argc,char* argv[])
{
    if(argc!=2){
        Usage(argv[0]);
        exit(1);
    }
    PollServer ps(atoi(argv[1]));
    ps.PollServerInit();
    ps.Start();
    return 0;
}
