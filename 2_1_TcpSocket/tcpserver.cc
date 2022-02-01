#include"tcpserver.hpp"


int main()
{
    TcpServer ts;
    ts.TcpServerInit();
    ts.TcpServerStart();
    return 0;
}
