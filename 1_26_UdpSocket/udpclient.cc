#include"udpclient.hpp"



/*void Usage(char* str)
{
    std::cout<<"Usage:"<<std::endl;
    std::cout<<str<<" Server_IP"<<" Server_Port"<<std::endl;
}*/
int main(int argc,char* argv[])
{
   /* if(argc!=3){
        Usage(argv[0]);
        exit(4);
    }
    UdpClient uc(argv[1],atoi(argv[2]));*/
    UdpClient uc;
    uc.UdpClientInit();
    uc.Start();
    return 0;
}
