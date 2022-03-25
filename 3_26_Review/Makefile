FLAG=-std=c++11
.PHONY:all 
all:httpServer httpClient 
httpServer:httpServer.cc tcpServer.cc ThreadPool.cc 
	g++ -o $@ $^ $(FLAG) -lpthread
httpClient:httpClient.cc tcpClient.cc
	g++ -o $@ $^ $(FLAG)
.PHONY:clean
clean:
	rm -f httpServer httpClient 
