#include"udpserver.hpp"




/*void Usage(char* str)
{
    std::cout<<"Usage:"<<std::endl;
    std::cout<<str<<" Server_IP"<<" Server_Port"<<std::endl;
}*/
int main(int argc,char* argv[])
{
   /* if(argc!=3){
        Usage(argv[0]);
        exit(3);
    }
    UdpServer us(argv[1],atoi(argv[2]));*/
    UdpServer us;
    us.UdpServerInit();
    us.Start();
    return 0;
}
