
FLAG=-std=c++11 -lpthread
.PHONY:all
all:myBlock selectServer selectClient
myBlock:myBlock.cc 
	g++ -o $@ $^ 
selectServer:selectServer.cc sock.hpp server.cc 
	g++ -o $@ $^ $(FLAG)
selectClient:selectClient.cc sock.hpp client.cc  
	g++ -o $@ $^ $(FLAG)

.PHONY:clean
clean:
	rm -f myBlock selectServer selectClient 
