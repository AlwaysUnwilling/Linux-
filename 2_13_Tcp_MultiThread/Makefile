.PHONY:all
all:TcpServer TcpClient
TcpServer:TcpServer.cc
	g++ -o $@ $^ -lpthread
TcpClient:TcpClient.cc
	g++ -o $@ $^ -lpthread
.PHONY:clean
clean:
	rm -f TcpServer TcpClient
