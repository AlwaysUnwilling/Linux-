#include"TcpClient.hpp"


int main()
{
    TcpClient tc;
    tc.TcpClientInit();
    tc.Start();
    return 0;
}
