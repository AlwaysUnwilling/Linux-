#include"tcpclient.hpp"


int main()
{
    TcpClient tc;
    tc.TcpClientInit();
    tc.TcpClientStart();
    return 0;
}
