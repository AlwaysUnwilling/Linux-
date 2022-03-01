#include"SelectServer.hpp"


void Usage(std::string str)
{
    std::cout<<"Usage:\n\t"<<str<<" "<<"Port"<<std::endl;
}
int main(int argc,char* argv[])
{
    if(argc!=2){
        Usage(argv[0]);
        exit(1);
    }
    SelectServer* ss=new SelectServer(atoi(argv[1]));
    ss->SelectServerInit();
    ss->Start();
    return 0;
}
