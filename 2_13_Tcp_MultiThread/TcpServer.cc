#include"TcpServer.hpp"


int main()
{
    TcpServer ts;
    ts.TcpServerInit();
    ts.Start();
    return 0;
}
